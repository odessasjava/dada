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
#include <cstring>

#ifdef _WIN32
# include "GL/wglext.h"
#else
# include <GL/glx.h>
#endif

static const char* g_extensions = NULL;


#ifndef DADA_WITH_GLEW

//---------------------------------------------------------
// VERSION_1_3
//---------------------------------------------------------
#if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)

/*PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;*/

#endif // VERSION_1_3

//---------------------------------------------------------
// VERSION_1_5
//---------------------------------------------------------
#if !defined(DADA_GL_CORE_VERSION_1_5) && defined(GL_VERSION_1_5)

PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;

#endif // VERSION_1_5


//---------------------------------------------------------
// VERSION_3_0
//---------------------------------------------------------
#if !defined(DADA_GL_CORE_VERSION_3_0) && defined(GL_VERSION_3_0)

PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;

#endif // VERSION_3_0


PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;

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

/*PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;*/

#endif // DADA_WITH_GLEW


namespace dada
{

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
  
  void* p = wglGetProcAddress(name);
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
  if (p != NULL)
  {
    getLog() << "STATUS: Initialized GL extension " << name << endl;
  }
  else
  {
    getLog() << "ERROR! Failed to initialize GL extension " << name << endl;
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

bool initGL()
{
  const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  if (vendor != NULL)
  {
    getLog() << "STATUS: GL vendor is " << vendor << endl;
  }
  
  const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  if (renderer != NULL)
  {
    getLog() << "STATUS: GL renderer is " << renderer << endl;
  }

  const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (version != NULL)
  {
    getLog() << "STATUS: GL version as text is " << version << endl;
  }

  int major = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  if (major != 0)
  {
    int minor = 0;
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    getLog() << "STATUS: GL version as int is " << major << '.' << minor << endl;
  }

  const char* glsl_version = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
  if (glsl_version != NULL)
  {
    getLog() << "STATUS: GLSL version is " << glsl_version << endl;
  }
  
  g_extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
  if (g_extensions != NULL)
  {
    getLog() << "STATUS: GL extensions as text are " << g_extensions << endl;
    printExtensions(g_extensions);
  }
  
  
# ifdef DADA_WITH_GLEW

  if (glewInit() != GLEW_OK)
  {
    getLog() << "ERROR! Failed to initialize GLEW" << endl;
  }
  
# else // DADA_WITH_GLEW
  

# if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)
  
  /*DADA_INIT_FN(glActiveTexture, PFNGLACTIVETEXTUREPROC, "glActiveTexture");
  
  DADA_INIT_FN(glCompressedTexImage2D, PFNGLCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2D");
  DADA_INIT_FN(glCompressedTexSubImage2D, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2D");*/
  
# endif // VERSION_1_3
  

# if !defined(DADA_GL_CORE_VERSION_1_5) && defined(GL_VERSION_1_5)
  
  DADA_INIT_FN(glBindBuffer, PFNGLBINDBUFFERPROC, "glBindBuffer");
  DADA_INIT_FN(glBufferData, PFNGLBUFFERDATAPROC, "glBufferData");
  DADA_INIT_FN(glBufferSubData, PFNGLBUFFERSUBDATAPROC, "glBufferSubData");
  DADA_INIT_FN(glDeleteBuffers, PFNGLDELETEBUFFERSARBPROC, "glDeleteBuffers");
  DADA_INIT_FN(glGenBuffers, PFNGLGENBUFFERSPROC, "glGenBuffers");
  DADA_INIT_FN(glGetBufferParameteriv, PFNGLGETBUFFERPARAMETERIVPROC, "glGetBufferParameteriv");
  DADA_INIT_FN(glIsBuffer, PFNGLISBUFFERPROC, "glIsBuffer");

# endif // VERSION_1_5
  

# if !defined(DADA_GL_CORE_VERSION_3_0) && defined(GL_VERSION_3_0)
  
  DADA_INIT_FN(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC, "glBindVertexArray");
  DADA_INIT_FN(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC, "glDeleteVertexArrays");
  DADA_INIT_FN(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC, "glGenVertexArrays");

# endif // VERSION_3_0

  DADA_INIT_FN(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC, "glDisableVertexAttribArray");
  DADA_INIT_FN(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC, "glEnableVertexAttribArray");
  DADA_INIT_FN(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC, "glVertexAttribPointer");
  
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
  
  /*DADA_INIT_FN(glBindFramebuffer, PFNGLBINDFRAMEBUFFERPROC, "glBindFramebuffer");
  DADA_INIT_FN(glCheckFramebufferStatus, PFNGLCHECKFRAMEBUFFERSTATUSPROC, "glCheckFramebufferStatus");
  DADA_INIT_FN(glDeleteFramebuffers, PFNGLDELETEFRAMEBUFFERSPROC, "glDeleteFramebuffers");
  DADA_INIT_FN(glFramebufferTexture2D, PFNGLFRAMEBUFFERTEXTURE2DPROC, "glFramebufferTexture2D");
  DADA_INIT_FN(glGenFramebuffers, PFNGLGENFRAMEBUFFERSPROC, "glGenFramebuffers");*/
  
#endif // DADA_WITH_GLEW

  return true;
}

} // dada
