//---------------------------------------------------------
//
//  Project:      dada
//  Module:       app
//  File:         Application.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_APP_APPLICATION_H
#define DADA_APP_APPLICATION_H

#include "dada/core/common.h" //
//#include "dada/gl/GL.h" //

namespace dada
{

class WindowInfo
{
public:
  WindowInfo();
  const char* getTitle() const;
  uint16_t getWidth() const;
  uint16_t getHeight() const;
  uint8_t getBPP() const;
  bool isFullscreen() const;
  bool isDoubleBuffer() const;

private:
  const char* m_title;
  uint16_t m_width;
  uint16_t m_height;
  uint8_t  m_bpp;
  bool m_fullscreen;
  bool m_double_buffer;
};

class DrawHandler
{
public:
  virtual void draw()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }
};

class KeyboardHandler
{
public:
  virtual void down(uint8_t code) {}
};

class ResizeHandler
{
public:
  virtual void resize(uint16_t width, uint16_t height)
  {
    glViewport(0, 0, width, height);
  }
};

class Application
{
public:
  Application();
  ~Application();
  bool isInited() const;
  const WindowInfo& getInfo() const;
  bool createWindow(const WindowInfo& info);
  void destroyWindow();
  void run();
  uint64_t getDeltaTime();

  DrawHandler* getDrawHandler();
  void setDrawHandler(DrawHandler* handler);
  KeyboardHandler* getKeyboardHandler();
  void setKeyboardHandler(KeyboardHandler* keyboard_handler);
  ResizeHandler* getResizeHandler();
  void setResizeHandler(ResizeHandler* handler);
  static const char* getClassName();

private:
  bool createWindowWin();
  void destroyWindowWin();
  void runWin();
  uint64_t getDeltaTimeWin();
  bool createWindowX();
  void destroyWindowX();
  void runX();
  
private:
  WindowInfo m_info;
  DrawHandler* m_draw_handler;
  KeyboardHandler* m_keyboard_handler;
  ResizeHandler* m_resize_handler;
  void* m_instance;
  void* m_wnd;
  void* m_dc;
  void* m_rc;
  
  void* m_display;
  unsigned long m_window;

  uint64_t m_prev_time;
};



inline WindowInfo::WindowInfo() :
  m_title("Dada"),
  m_width(1200),
  m_height(600),
  m_bpp(24),
  m_fullscreen(false),
  m_double_buffer(true)
{
}

inline const char* WindowInfo::getTitle() const
{
  return m_title;
}

inline uint16_t WindowInfo::getWidth() const
{
  return m_width;
}

inline uint16_t WindowInfo::getHeight() const
{
  return m_height;
}

inline uint8_t WindowInfo::getBPP() const
{
  return m_bpp;
}

inline bool WindowInfo::isFullscreen() const
{
  return m_fullscreen;
}

inline bool WindowInfo::isDoubleBuffer() const
{
  return m_double_buffer;
}



inline bool Application::isInited() const
{
  return m_wnd != NULL;
}

inline const WindowInfo& Application::getInfo() const
{
  return m_info;
}

inline DrawHandler* Application::getDrawHandler()
{
  return m_draw_handler;
}

inline void Application::setDrawHandler(DrawHandler* handler)
{
  m_draw_handler = handler;
}

inline KeyboardHandler* Application::getKeyboardHandler()
{
  return m_keyboard_handler;
}

inline void Application::setKeyboardHandler(KeyboardHandler* keyboard_handler)
{
  m_keyboard_handler = keyboard_handler;
}

inline ResizeHandler* Application::getResizeHandler()
{
  return m_resize_handler;
}

inline void Application::setResizeHandler(ResizeHandler* handler)
{
  m_resize_handler = handler;
}

inline const char* Application::getClassName()
{
  return "Dada_Window";
}

} // dada

#endif // DADA_APP_APPLICATION_H
