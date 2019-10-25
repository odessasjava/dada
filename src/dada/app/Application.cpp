//---------------------------------------------------------
//
//  Project:      dada
//  Module:       app
//  File:         Application.cpp
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#include "dada/gl/GL.h"

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include<X11/X.h>
# include<X11/Xlib.h>
# include<GL/glx.h>
#endif

#include "EGL/egl.h"

#include <cstdio>
#include "dada/app/Application.h"
#include "dada/core/Log.h"

namespace dada
{

#ifdef _WIN32

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM param_word, LPARAM param_long)
{
  Application* app = NULL;
  if (msg == WM_CREATE)
  {
    LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(param_long);
    app = static_cast<Application*>(lpcs->lpCreateParams);
    SetWindowLong(wnd, GWLP_USERDATA, reinterpret_cast<LONG>(app));
  }
  else
  {
    app = reinterpret_cast<Application*>(GetWindowLongPtr(wnd, GWLP_USERDATA));
  }

  if (app != NULL)
  {
    switch (msg)									// Check For Windows Messages
    {
      case WM_ACTIVATE:							// Watch For Window Activate Message
      {
        //if (!HIWORD(wParam))					// Check Minimization State
        //{
        //	active=TRUE;						// Program Is Active
        //}
        //else
        //{
        //	active=FALSE;						// Program Is No Longer Active
        //}

        return 0;								// Return To The Message Loop
      }

      case WM_SYSCOMMAND:							// Intercept System Commands
      {
        //switch (wParam)							// Check System Calls
        //{
        //	case SC_SCREENSAVE:					// Screensaver Trying To Start?
        //	case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
        //	return 0;							// Prevent From Happening
        //}
        break;									// Exit
      }

      case WM_CLOSE:								// Did We Receive A Close Message?
      {
        PostQuitMessage(0);						// Send A Quit Message
        return 0;								// Jump Back
      }

      case WM_KEYDOWN:							// Is A Key Being Held Down?
      {
        KeyboardHandler* handler = app->getKeyboardHandler();
        if (handler != NULL)
        {
          handler->down(param_word);
        }
        return 0;								// Jump Back
      }

      case WM_KEYUP:								// Has A Key Been Released?
      {
        //keys[wParam] = FALSE;					// If So, Mark It As FALSE
        return 0;								// Jump Back
      }

      case WM_SIZE:
      {
        ResizeHandler* handler = app->getResizeHandler();
        if (handler != NULL)
        {
          handler->resize(LOWORD(param_long), HIWORD(param_long));
        }
        return 0;
      }
    }
  }

  return DefWindowProc(wnd, msg, param_word, param_long);
}

bool Application::createWindowWin()
{
  m_instance = GetModuleHandle(NULL);
  HICON icon = LoadIcon(NULL, IDI_APPLICATION);

  WNDCLASSEX wc;
  memset(&wc, 0, sizeof(wc));
  wc.cbSize = sizeof(wc);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbWndExtra = sizeof(LONG_PTR);
  wc.hInstance = static_cast<HINSTANCE>(m_instance);
  wc.hIcon = icon;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = getClassName();
  wc.hIconSm = icon;
  if (!RegisterClassEx(&wc))
  {
    getLog() << "ERROR: Failed to register the window class" << endl;
    return false;
  }

  DWORD style;
  DWORD exstyle;
  if (m_info.isFullscreen())
  {
    DEVMODE dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = m_info.getWidth();
    dm.dmPelsHeight = m_info.getHeight();
    dm.dmBitsPerPel = m_info.getBPP();
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      getLog() << "ERROR: Failed to setup display settings" << endl;
      return false;
    }
    style = WS_POPUP;
    exstyle = WS_EX_APPWINDOW;
    ShowCursor(FALSE);
  }
  else
  {
    style = WS_OVERLAPPEDWINDOW;
    exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  }

  RECT rect;
  rect.left = 0;
  rect.right = m_info.getWidth();
  rect.top = 0;
  rect.bottom = m_info.getHeight();
  AdjustWindowRectEx(&rect, style, FALSE, exstyle);

  style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  m_wnd = CreateWindowEx
  (
    exstyle, getClassName(), m_info.getTitle(), style,
    0, 0, rect.right - rect.left, rect.bottom - rect.top,
    NULL, NULL, static_cast<HINSTANCE>(m_instance), this
  );
  if (m_wnd == NULL)
  {
    getLog() << "ERROR: Failed to create window" << endl;
    destroyWindow();
    return false;
  }

  m_dc = GetDC(static_cast<HWND>(m_wnd));
  if (m_dc == NULL)
  {
    getLog() << "ERROR: Failed to create device context" << endl;
    destroyWindow();
    return false;
  }

  PIXELFORMATDESCRIPTOR pfd;
  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = m_info.getBPP();
  pfd.iLayerType = PFD_MAIN_PLANE;
  if (m_info.isDoubleBuffer())
  {
    pfd.dwFlags |= PFD_DOUBLEBUFFER;
  }

  int pf = ChoosePixelFormat(static_cast<HDC>(m_dc), &pfd);
  if (pf == 0)
  {
    getLog() << "ERROR: Unable to find a suitable pixel format" << endl;
    destroyWindow();
    return false;
  }

  if (!SetPixelFormat(static_cast<HDC>(m_dc), pf, &pfd))
  {
    getLog() << "ERROR: Failed to set the pixel format" << endl;
    destroyWindow();
    return false;
  }

  /*m_rc = wglCreateContext(static_cast<HDC>(m_dc));
  if (m_rc == NULL)
  {
    getLog() << "ERROR: Failed to create the rendering context" << endl;
    destroyWindow();
    return false;
  }

  if (!wglMakeCurrent(static_cast<HDC>(m_dc), static_cast<HGLRC>(m_rc)))
  {
    getLog() << "ERROR: Unable to activate the rendering context" << endl;
    destroyWindow();
    return false;
  }*/

  // Get Display
  EGLDisplay display = eglGetDisplay(static_cast<HDC>(m_dc));
  if ( display == EGL_NO_DISPLAY )
  {
    return false;
  }

  // Initialize EGL
  EGLint majorVersion;
  EGLint minorVersion;
  if (!eglInitialize(display, &majorVersion, &minorVersion))
  {
    return false;
  }

  // Get configs
  EGLint numConfigs;
  if (!eglGetConfigs(display, NULL, 0, &numConfigs))
  {
    return false;
  }

  // Choose config
  EGLint attribList[] =
  {
    EGL_RED_SIZE,       5,
    EGL_GREEN_SIZE,     6,
    EGL_BLUE_SIZE,      5,
    EGL_ALPHA_SIZE,     /*(flags & ES_WINDOW_ALPHA) ? 8 :*/ EGL_DONT_CARE,
    EGL_DEPTH_SIZE,     /*(flags & ES_WINDOW_DEPTH) ? 8 :*/ EGL_DONT_CARE,
    EGL_STENCIL_SIZE,   /*(flags & ES_WINDOW_STENCIL) ? 8 :*/ EGL_DONT_CARE,
    EGL_SAMPLE_BUFFERS, /*(flags & ES_WINDOW_MULTISAMPLE) ? 1 :*/ 0,
    EGL_NONE
  };
  EGLConfig config;
  if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
  {
    return false;
  }

  // Create a surface
  EGLSurface surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)(static_cast<HWND>(m_wnd)), NULL);
  if (surface == EGL_NO_SURFACE)
  {
    return false;
  }

  // Create a GL context
  EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
  EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
  if (context == EGL_NO_CONTEXT)
  {
    return false;
  }
  
  // Make the context current
  if (!eglMakeCurrent(display, surface, surface, context))
  {
    return false;
  }




  if (!GL::init())
  {
    return false;
  }

  ShowWindow(static_cast<HWND>(m_wnd), SW_SHOW);
  SetForegroundWindow(static_cast<HWND>(m_wnd));
  SetFocus(static_cast<HWND>(m_wnd));

  return true;
}

void Application::destroyWindowWin()
{
  if (m_info.isFullscreen())
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);
  }

  /*if (m_rc != NULL)
  {
    if (!wglMakeCurrent(NULL, NULL))
    {
      getLog() << "ERROR: Unable to deactivate the GL rendering context" << endl;
    }
    if (!wglDeleteContext(static_cast<HGLRC>(m_rc)))
    {
      getLog() << "ERROR: Failed to release rendering context" << endl;
    }
    m_rc = NULL;
  }*/

  if (m_dc != NULL)
  {
    if (ReleaseDC(static_cast<HWND>(m_wnd), static_cast<HDC>(m_dc)) == 0)
    {
      getLog() << "ERROR: Failed to release device context" << endl;
      m_dc = NULL;
    }
  }

  if (m_wnd != NULL)
  {
    if (!DestroyWindow(static_cast<HWND>(m_wnd)))
    {
      getLog() << "ERROR: Failed to release window" << endl;
      m_wnd = NULL;
    }
  }

  if (!UnregisterClass(getClassName(), static_cast<HINSTANCE>(m_instance)))
  {
    getLog() << "ERROR: Failed to unregister window class" << endl;
    m_instance = NULL;
  }
}

void Application::runWin()
{
  bool done = false;
  while (!done)
  {
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        done = true;
      }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else
    {
      if (m_draw_handler != NULL)
      {
        m_draw_handler->draw();
        if (m_info.isDoubleBuffer())
        {
          SwapBuffers(static_cast<HDC>(m_dc));
        }
        else
        {
          glFinish();
        }
      }
    }
  }
}

uint64_t Application::getDeltaTimeWin()
{
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);

  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  
  uint64_t curr_time = counter.QuadPart;
  curr_time *= 1000000; // usec
  curr_time /= frequency.QuadPart;

  const uint64_t delta_time = curr_time - m_prev_time;
  m_prev_time = curr_time;
  return delta_time;
}

#else

bool Application::createWindowX()
{
  Display                 *dpy;
  Window                  root;
  GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
  XVisualInfo             *vi;
  Colormap                cmap;
  XSetWindowAttributes    swa;
  Window                  win;
  GLXContext              glc;
  //XWindowAttributes       gwa;
  //XEvent                  xev;
  
  
  dpy = XOpenDisplay(NULL);
 
 if(dpy == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        //exit(0);
        return false;
 }
        
 root = DefaultRootWindow(dpy);

 vi = glXChooseVisual(dpy, 0, att);

 if(vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        //exit(0);
        return false;
 } 
 else {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
 }


 cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 swa.colormap = cmap;
 swa.event_mask = ExposureMask | KeyPressMask;
 
 win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

 XMapWindow(dpy, win);
 XStoreName(dpy, win, "VERY SIMPLE APPLICATION");
 
 glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
 glXMakeCurrent(dpy, win, glc);
  
 
 
 
 m_display = dpy;
 m_window = win;
 
 if (!initGL())
  {
    return false;
  }
 
  return true;
}

void Application::destroyWindowX()
{
  
}

void Application::runX()
{
  bool done = false;
  while (!done)
  {
    XEvent xev;
    
    Display *dpy = static_cast<Display*>(m_display);
    
    XNextEvent(dpy, &xev);
    
    if(xev.type == Expose)
    {
      XWindowAttributes       gwa;
      XGetWindowAttributes(dpy, m_window, &gwa);
      
      
      if (m_resize_handler != NULL)
      {
        m_resize_handler->resize(gwa.width, gwa.height);
      }
      
      //glViewport(0, 0, gwa.width, gwa.height);
      //DrawAQuad(); 
      //glXSwapBuffers(dpy, win);
      
      
      if (m_draw_handler != NULL)
      {
        m_draw_handler->draw();
        if (m_info.isDoubleBuffer())
        {
          glXSwapBuffers(dpy, m_window);
        }
        else
        {
          glFinish();
        }
      }
    }
                
        /*else if(xev.type == KeyPress) {
                glXMakeCurrent(dpy, None, NULL);
                glXDestroyContext(dpy, glc);
                XDestroyWindow(dpy, win);
                XCloseDisplay(dpy);
                exit(0);
        }*/
    
    
  }
}

#endif

Application::Application() :
  m_info(),
  m_draw_handler(NULL),
  m_keyboard_handler(NULL),
  m_resize_handler(NULL),
  m_instance(NULL),
  m_wnd(NULL),
  m_dc(NULL),
  m_rc(NULL),
  m_prev_time(getDeltaTimeWin())
{
}

Application::~Application()
{
  destroyWindow();
}

bool Application::createWindow(const WindowInfo& info)
{
  m_info = info;
  
  bool res = false;
# ifdef _WIN32
  res = createWindowWin();
# else
  res = createWindowX();
# endif
  return res;
}

void Application::destroyWindow()
{
# ifdef _WIN32
  destroyWindowWin();
# else
  destroyWindowX();
# endif
}

void Application::run()
{
# ifdef _WIN32
  runWin();
# else
  runX();
# endif
}

uint64_t Application::getDeltaTime()
{
  uint64_t res;
# ifdef _WIN32
  res = getDeltaTimeWin();
# else
  res = getDeltaTimeX();
# endif
  return res;
}

} // dada
