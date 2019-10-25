//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         GL.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/gl/GL.h"
#include "dada/core/Log.h"
#include <cstdlib>
#include <cstring>

#include "EGL/egl.h"

#ifdef _WIN32
# include "GL/wglext.h"
#else
# include <GL/glx.h>
#endif




#ifndef DADA_WITH_GLEW


PFNGLCLEARPROC glClear = NULL;
PFNGLCLEARCOLORPROC glClearColor = NULL;
PFNGLENABLEPROC glEnable = NULL;
PFNGLFINISHPROC glFinish = NULL;
PFNGLGETERRORPROC glGetError = NULL;
PFNGLGETINTEGERVPROC glGetIntegerv = NULL;
PFNGLGETSTRINGPROC glGetString = NULL;
PFNGLVIEWPORTPROC glViewport = NULL;


PFNGLDRAWELEMENTSPROC glDrawElements = NULL;


/*
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;


PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
*/



/*#ifdef GL_OES_vertex_array_object
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES = NULL;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES = NULL;
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES = NULL;
#endif*/


//---------------------------------------------------------
// VERSION_1_3
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)

PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;

/*PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;*/

//#endif // VERSION_1_3


//---------------------------------------------------------
// VERSION_1_5
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_1_5) && defined(GL_VERSION_1_5)

PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;

//#endif // VERSION_1_5


//---------------------------------------------------------
// VERSION_2_0
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_2_0) && defined(GL_VERSION_2_0)

PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;

//#endif // VERSION_2_0


//---------------------------------------------------------
// VERSION_3_0
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_3_0) && defined(GL_VERSION_3_0)

PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;

//#endif // VERSION_3_0



/*PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;*/

#endif // DADA_WITH_GLEW


namespace dada
{

int GL::m_major = 0;
int GL::m_minor = 0;
const char* GL::m_vendor = NULL;
const char* GL::m_renderer = NULL;
const char* GL::m_version = NULL;
const char* GL::m_glsl_version = NULL;
const char* GL::m_extensions = NULL;

static void parseVersion(const char* version, int& major, int& minor)
{
  char* end = NULL;
  major = strtol(version, &end, 10);
  if (major != 0)
  {
    if (*end == '.')
    {
      const char* p = end + 1;
      if (*p != '\0')
      {
        minor = strtol(p, NULL, 10);
      }
    }
  }
  else
  {
    const char* last = strrchr(version, ' ');
    if (last != NULL)
    {
      char* end = NULL;
      major = strtol(last, &end, 10);
      if (major != 0)
      {
        if (*end == '.')
        {
          const char* p = end + 1;
          if (*p != '\0')
          {
            minor = strtol(p, NULL, 10);
          }
        }
      }
    }
  }
}

static bool isExtSupported(const char* ext, const char* extensions)
{
  const char* start = extensions;
  const char* ptr;
  while ((ptr = strstr(start, ext)) != NULL)
  {
    const char* end = ptr + strlen(ext);
    if (*end == ' ' || *end == '\0')
    {
      return true;
    }
    start = end;
  }
  return false;
}

static void* getGLFuncAddress(const char* name)
{
# ifdef _WIN32
  
  //void* p = wglGetProcAddress(name);
  void* p = eglGetProcAddress(name);
  if (p == NULL)
  {
    HMODULE module = LoadLibraryA("opengl32.dll");
    p = GetProcAddress(module, name);
  }

# else
  
  const GLubyte* nameBytes = reinterpret_cast<const GLubyte*>(name);
  void* p = reinterpret_cast<void*>(glXGetProcAddress(nameBytes));

# endif
  
  return p;
}

static void* getGLFuncAddressLogged(const char* name)
{
  void* p = getGLFuncAddress(name);
  if (p == NULL)
  {
    getLog() << "ERROR! Failed to initialize GL function " << name << endl;
  }
  return p;
}

#define DADA_INIT_FN(var, type, name) \
  do { var = (type)getGLFuncAddressLogged(name); } while (0);

#define DADA_INIT_NEEDED_FN(var, type, name) \
  do { var = (type)getGLFuncAddressLogged(name); if (var == NULL) return false; } while (0);

static void printExtensions(const char* extensions)
{
  getLog() << "STATUS: GL extensions as list are:" << endl;
  
  size_t index = 1;

  const char* start = extensions;
  do 
  {
    const size_t len = strcspn(start, " ");
    if (len > 0)
    {
      getLog() << "  " << index << ". ";
      for (size_t i = 0; i < len; ++i)
      {
        getLog() << start[i];
      }
      getLog() << endl;

      start += len + 1;

      ++index;
    }
  } while (*start != '\0');
}

bool GL::initCore()
{
  DADA_INIT_NEEDED_FN(glClear, PFNGLCLEARPROC, "glClear");
  DADA_INIT_NEEDED_FN(glClearColor, PFNGLCLEARCOLORPROC, "glClearColor");
  DADA_INIT_NEEDED_FN(glEnable, PFNGLENABLEPROC, "glEnable");
  DADA_INIT_NEEDED_FN(glFinish, PFNGLFINISHPROC, "glFinish");
  DADA_INIT_NEEDED_FN(glGetError, PFNGLGETERRORPROC, "glGetError");
  DADA_INIT_NEEDED_FN(glGetIntegerv, PFNGLGETINTEGERVPROC, "glGetIntegerv");
  DADA_INIT_NEEDED_FN(glGetString, PFNGLGETSTRINGPROC, "glGetString");
  DADA_INIT_NEEDED_FN(glViewport, PFNGLVIEWPORTPROC, "glViewport");

  return true;
}

bool GL::initInfo()
{
  m_vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  GLenum err = glGetError();
  if (err == GL_NO_ERROR && m_vendor != NULL)
  {
    getLog() << "STATUS: GL vendor is \"" << m_vendor << '\"' << endl;
  }
  
  m_renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  err = glGetError();
  if (err == GL_NO_ERROR && m_renderer != NULL)
  {
    getLog() << "STATUS: GL renderer is \"" << m_renderer << '\"' << endl;
  }

  m_version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  err = glGetError();
  if (err == GL_NO_ERROR && m_version != NULL)
  {
    getLog() << "STATUS: GL version as text is \"" << m_version << '\"' << endl;
  }

  glGetIntegerv(GL_MAJOR_VERSION, &m_major);
  err = glGetError();
  if (err == GL_NO_ERROR && m_major != 0)
  {
    glGetIntegerv(GL_MINOR_VERSION, &m_minor);
    err = glGetError();
    if (err == GL_NO_ERROR)
    {
      getLog() << "STATUS: GL version as int is " << m_major << '.' << m_minor << endl;
    }
  }

  if (m_major == 0 && m_minor == 0 && m_version != NULL)
  {
    parseVersion(m_version, m_major, m_minor);
  }

  if (m_major > 0 && m_minor >= 0)
  {
    getLog() << "STATUS: GL version processed as " << m_major << '.' << m_minor << endl;
  }
  else
  {
    getLog() << "ERROR! Failed to process GL version " << m_major << '.' << m_minor << endl;
    return false;
  }

  m_glsl_version = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
  err = glGetError();
  if (err == GL_NO_ERROR && m_glsl_version != NULL)
  {
    getLog() << "STATUS: GLSL version is \"" << m_glsl_version << '\"' << endl;
  }
  
  m_extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
  err = glGetError();
  if (err == GL_NO_ERROR && m_extensions != NULL)
  {
    getLog() << "STATUS: GL extensions as text are \"" << m_extensions << '\"' << endl;
    printExtensions(m_extensions);
  }

  return true;
}

bool GL::initExtensions()
{
  DADA_INIT_FN(glDrawElements, PFNGLDRAWELEMENTSPROC, "glDrawElements");

  

//# if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)
  
  DADA_INIT_FN(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC, "glDisableVertexAttribArray");
  DADA_INIT_FN(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC, "glEnableVertexAttribArray");
  DADA_INIT_FN(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC, "glVertexAttribPointer");
  

  /*DADA_INIT_FN(glActiveTexture, PFNGLACTIVETEXTUREPROC, "glActiveTexture");
  
  DADA_INIT_FN(glCompressedTexImage2D, PFNGLCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2D");
  DADA_INIT_FN(glCompressedTexSubImage2D, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2D");*/
  
//# endif // VERSION_1_3
  

//# if !defined(DADA_GL_CORE_VERSION_1_5) && defined(GL_VERSION_1_5)
  
  DADA_INIT_FN(glBindBuffer, PFNGLBINDBUFFERPROC, "glBindBuffer");
  DADA_INIT_FN(glBufferData, PFNGLBUFFERDATAPROC, "glBufferData");
  DADA_INIT_FN(glBufferSubData, PFNGLBUFFERSUBDATAPROC, "glBufferSubData");
  DADA_INIT_FN(glDeleteBuffers, PFNGLDELETEBUFFERSPROC, "glDeleteBuffers");
  DADA_INIT_FN(glGenBuffers, PFNGLGENBUFFERSPROC, "glGenBuffers");
  DADA_INIT_FN(glGetBufferParameteriv, PFNGLGETBUFFERPARAMETERIVPROC, "glGetBufferParameteriv");
  DADA_INIT_FN(glIsBuffer, PFNGLISBUFFERPROC, "glIsBuffer");

//# endif // VERSION_1_5
  

//# if !defined(DADA_GL_CORE_VERSION_2_0) && defined(GL_VERSION_2_0)
  
  DADA_INIT_FN(glAttachShader, PFNGLATTACHSHADERPROC, "glAttachShader");
  DADA_INIT_FN(glCompileShader, PFNGLCOMPILESHADERPROC, "glCompileShader");
  DADA_INIT_FN(glCreateProgram, PFNGLCREATEPROGRAMPROC, "glCreateProgram");
  DADA_INIT_FN(glCreateShader, PFNGLCREATESHADERPROC, "glCreateShader");
  DADA_INIT_FN(glDeleteProgram, PFNGLDELETEPROGRAMPROC, "glDeleteProgram");
  DADA_INIT_FN(glDeleteShader, PFNGLDELETESHADERPROC, "glDeleteShader");
  DADA_INIT_FN(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC, "glGetAttribLocation");
  DADA_INIT_FN(glGetProgramiv, PFNGLGETPROGRAMIVPROC, "glGetProgramiv");
  DADA_INIT_FN(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC, "glGetProgramInfoLog");
  DADA_INIT_FN(glGetShaderiv, PFNGLGETSHADERIVPROC, "glGetShaderiv");
  DADA_INIT_FN(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC, "glGetShaderInfoLog");
  DADA_INIT_FN(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC, "glGetUniformLocation");
  DADA_INIT_FN(glLinkProgram, PFNGLLINKPROGRAMPROC, "glLinkProgram");
  DADA_INIT_FN(glShaderSource, PFNGLSHADERSOURCEPROC, "glShaderSource");
  DADA_INIT_FN(glUniform1i, PFNGLUNIFORM1IPROC, "glUniform1i");
  DADA_INIT_FN(glUniform1f, PFNGLUNIFORM1FPROC, "glUniform1f");
  DADA_INIT_FN(glUniform3fv, PFNGLUNIFORM3FVPROC, "glUniform3fv");
  DADA_INIT_FN(glUniform4fv, PFNGLUNIFORM4FVPROC, "glUniform4fv");
  DADA_INIT_FN(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC, "glUniformMatrix4fv");
  DADA_INIT_FN(glUseProgram, PFNGLUSEPROGRAMPROC, "glUseProgram");

//# endif // VERSION_3_0


//# if !defined(DADA_GL_CORE_VERSION_3_0) && defined(GL_VERSION_3_0)
  
  DADA_INIT_FN(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC, "glBindVertexArray");
  if (glBindVertexArray == NULL)
  {
  //  DADA_INIT_FN(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC, "glBindVertexArrayOES");
  }

  DADA_INIT_FN(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC, "glDeleteVertexArrays");
  if (glDeleteVertexArrays == NULL)
  {
  //  DADA_INIT_FN(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC, "glDeleteVertexArraysOES");
  }
  

  if (m_major >= 3)
  {
    DADA_INIT_FN(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC, "glGenVertexArrays");
  }
  if (glGenVertexArrays == NULL && isExtSupported("GL_OES_vertex_array_object", m_extensions))
  {
    DADA_INIT_FN(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC, "glGenVertexArraysOES");
  }

//# endif // VERSION_3_0

  
  return true;
}

bool GL::init()
{
  return initCore() && initInfo() && initExtensions();
}

} // dada
