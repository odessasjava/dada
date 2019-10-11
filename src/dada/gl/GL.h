//---------------------------------------------------------
//
//  Project:      dada
//  Module:       gl
//  File:         GL.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_GL_GL_H
#define DADA_GL_GL_H

#include <GL/glew.h>

/*#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include "GL/gl.h"
#else
# include <GL/gl.h>
#endif


#ifdef GL_VERSION_1_1
# define DADA_GL_CORE_VERSION_1_1
#endif
#ifdef GL_VERSION_1_2
# define DADA_GL_CORE_VERSION_1_2
#endif
#ifdef GL_VERSION_1_3
# define DADA_GL_CORE_VERSION_1_3
#endif
#ifdef GL_VERSION_1_4
# define DADA_GL_CORE_VERSION_1_4
#endif
#ifdef GL_VERSION_1_5
# define DADA_GL_CORE_VERSION_1_5
#endif
#ifdef GL_VERSION_2_0
# define DADA_GL_CORE_VERSION_2_0
#endif
#ifdef GL_VERSION_2_1
# define DADA_GL_CORE_VERSION_2_1
#endif
#ifdef GL_VERSION_3_0
# define DADA_GL_CORE_VERSION_3_0
#endif
#ifdef GL_VERSION_3_1
# define DADA_GL_CORE_VERSION_3_1
#endif
#ifdef GL_VERSION_3_2
# define DADA_GL_CORE_VERSION_3_2
#endif
#ifdef GL_VERSION_3_3
# define DADA_GL_CORE_VERSION_3_3
#endif
#ifdef GL_VERSION_4_0
# define DADA_GL_CORE_VERSION_4_0
#endif
#ifdef GL_VERSION_4_1
# define DADA_GL_CORE_VERSION_4_1
#endif
#ifdef GL_VERSION_4_2
# define DADA_GL_CORE_VERSION_4_2
#endif
#ifdef GL_VERSION_4_3
# define DADA_GL_CORE_VERSION_4_3
#endif
#ifdef GL_VERSION_4_4
# define DADA_GL_CORE_VERSION_4_4
#endif
#ifdef GL_VERSION_4_5
# define DADA_GL_CORE_VERSION_4_5
#endif
#ifdef GL_VERSION_4_6
# define DADA_GL_CORE_VERSION_4_6
#endif



#include "GL/glext.h"


//---------------------------------------------------------
// VERSION_1_3
//---------------------------------------------------------
#if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)

//   1   GL_ARB_multitexture
// void glActiveTexture(GLenum texture);
extern PFNGLACTIVETEXTUREPROC glActiveTexture;

//  12   GL_ARB_texture_compression
// void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
// void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;

#endif // VERSION_1_3

////////////---------------------------------------------------------
// GL_VERSION_1_3
//////////---------------------------------------------------------
///////////#ifndef GL_VERSION_1_3
//  26   GL_ARB_vertex_program
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

//  30   GL_ARB_shader_objects
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC glUseProgram;

//  45   GL_ARB_framebuffer_object
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
*/

namespace dada
{

bool initGL();

} // dada

#endif // DADA_GL_GL_H