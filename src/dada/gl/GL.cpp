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
#include <cctype>
#include <cstring>

#ifdef _WIN32
# include "GL/wglext.h"
#else
# include <GL/glx.h>
#endif

static const char* g_extensions = NULL;

/*
//---------------------------------------------------------
// VERSION_1_3
//---------------------------------------------------------
#if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;

#endif // VERSION_1_3


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

PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
*/

namespace dada
{

static bool isExtSupported(const char* ext, const char* extensions)
{
  const char* start = extensions;
  const char* ptr;
  while ((ptr = strstr(start, ext)) != NULL)
  {
    const char* end = ptr + strlen(ext);
    if (isspace(*end) || *end == '\0')
    {
      return true;
    }
    start = end;
  }
  return false;
}

static void* getGLFuncAddress(const char* name)
{
#ifdef _WIN32
  void* p = wglGetProcAddress(name);
  if (p == NULL)
  {
    HMODULE module = LoadLibraryA("opengl32.dll");
    p = GetProcAddress(module, name);
  }
# else
  const GLubyte* nameBytes = reinterpret_cast<const GLubyte*>(name);
  void* p = reinterpret_cast<void*>(glXGetProcAddress(nameBytes));
  //if (p == NULL)
  //{
    //HMODULE module = LoadLibraryA("opengl32.dll");
    //p = GetProcAddress(module, name);
  //}
# endif
  return p;
}

static void* getGLFuncAddressLogged(const char* name)
{
  void* p = getGLFuncAddress(name);
  if (p == NULL)
  {
    getLog() << "ERROR! Failed to initialize GL extension " << name << endl;
  }
  return p;
}

#define DADA_INIT_FN(var, type, name) \
  do { var = (type)getGLFuncAddressLogged(name); if (var == NULL) return false; } while (0);

bool initGL()
{
  g_extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
  
  getLog() << "STATUS: GL vendor is " << reinterpret_cast<const char*>(glGetString(GL_VENDOR)) << endl;
  getLog() << "STATUS: GL renderer is " << reinterpret_cast<const char*>(glGetString(GL_RENDERER)) << endl;
  getLog() << "STATUS: GL version is " << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << endl;
  getLog() << "STATUS: GL extensions are " << g_extensions << endl;
  
  if (glewInit() != GLEW_OK)
  {
    getLog() << "ERROR! Failed to initialize GLEW" << endl;
  }
  
  /*
# if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)
  
  DADA_INIT_FN(glActiveTexture, PFNGLACTIVETEXTUREPROC, "glActiveTexture");
  
  DADA_INIT_FN(glCompressedTexImage2D, PFNGLCOMPRESSEDTEXIMAGE2DPROC, "glCompressedTexImage2D");
  DADA_INIT_FN(glCompressedTexSubImage2D, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, "glCompressedTexSubImage2D");
  
# endif // VERSION_1_3
  
  
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
  
  DADA_INIT_FN(glBindFramebuffer, PFNGLBINDFRAMEBUFFERPROC, "glBindFramebuffer");
  DADA_INIT_FN(glCheckFramebufferStatus, PFNGLCHECKFRAMEBUFFERSTATUSPROC, "glCheckFramebufferStatus");
  DADA_INIT_FN(glDeleteFramebuffers, PFNGLDELETEFRAMEBUFFERSPROC, "glDeleteFramebuffers");
  DADA_INIT_FN(glFramebufferTexture2D, PFNGLFRAMEBUFFERTEXTURE2DPROC, "glFramebufferTexture2D");
  DADA_INIT_FN(glGenFramebuffers, PFNGLGENFRAMEBUFFERSPROC, "glGenFramebuffers");
  */
  return true;
}

} // dada
