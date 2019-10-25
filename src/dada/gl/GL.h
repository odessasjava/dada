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

#ifdef DADA_WITH_GLEW

# include <GL/glew.h>

#else // DADA_WITH_GLEW

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
//# include "GL/gl.h"
# include "GLES3/gl3.h"
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



//#include "GL/glext.h"
#include "GLES2/gl2ext.h"


//
// GL_VERSION_1_0
//
//typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
//typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
//typedef void (APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
//typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
//typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
//typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
//typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
//typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
//typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
//typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
//typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
//typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
//typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
//typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum buf);
extern PFNGLCLEARPROC glClear;
extern PFNGLCLEARCOLORPROC glClearColor;
//typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
//typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
//typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
//typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
//typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
//typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
extern PFNGLENABLEPROC glEnable;
extern PFNGLFINISHPROC glFinish;
//typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
//typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
//typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum opcode);
//typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
//typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
//typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
//typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
//typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
//typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
//typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
//typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
//typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum pname, GLdouble *data);
extern PFNGLGETERRORPROC glGetError;
//typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
extern PFNGLGETINTEGERVPROC glGetIntegerv;
extern PFNGLGETSTRINGPROC glGetString;
//typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
//typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
//typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
//typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
//typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
//typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
//typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble n, GLdouble f);
extern PFNGLVIEWPORTPROC glViewport;


//
// GL_VERSION_1_1
//
//typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
extern PFNGLDRAWELEMENTSPROC glDrawElements;
//typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
//typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
//typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
//typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
//typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
//typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
//typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
//typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
//typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
//typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
//typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
//typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);


//
// GL_VERSION_1_5
//
//typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
//typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
//typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint id);
//typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
//typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
//typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
//typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
//typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
//extern PFNGLBINDBUFFERPROC glBindBuffer;
//extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
//extern PFNGLGENBUFFERSPROC glGenBuffers;
//typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
//typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
//typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
//typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
//typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
//typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
//typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
//typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);


//
// GL_VERSION_2_0
//
//typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
//typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
//typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
//typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
//typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
//extern PFNGLATTACHSHADERPROC glAttachShader;
//typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
//extern PFNGLCOMPILESHADERPROC glCompileShader;
//extern PFNGLCREATEPROGRAMPROC glCreateProgram;
//extern PFNGLCREATESHADERPROC glCreateShader;
//extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
//extern PFNGLDELETESHADERPROC glDeleteShader;
//typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
//typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
//typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
//typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
//typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
//typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
//extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
//extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
//extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
//extern PFNGLGETSHADERIVPROC glGetShaderiv;
//extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
//typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
//extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
//typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
//typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
//typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
//typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
//typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
//typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
//typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
//typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
//extern PFNGLLINKPROGRAMPROC glLinkProgram;
//extern PFNGLSHADERSOURCEPROC glShaderSource;
//extern PFNGLUSEPROGRAMPROC glUseProgram;
//typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
//typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
//typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
//typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
//typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
//typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
//typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
//typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
//typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
//typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
//typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);






//---------------------------------------------------------
// VERSION_1_3
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_1_3) && defined(GL_VERSION_1_3)

//  26   GL_ARB_vertex_program
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;


/*//   1   GL_ARB_multitexture
// void glActiveTexture(GLenum texture);
extern PFNGLACTIVETEXTUREPROC glActiveTexture;

//  12   GL_ARB_texture_compression
// void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
// void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;*/

//#endif // VERSION_1_3


//---------------------------------------------------------
// VERSION_1_5
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_1_5) && defined(GL_VERSION_1_5)

extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
extern PFNGLISBUFFERPROC glIsBuffer;

//#endif // VERSION_1_5


//---------------------------------------------------------
// VERSION_2_0
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_2_0) && defined(GL_VERSION_2_0)

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

//#endif // VERSION_2_0


//---------------------------------------------------------
// VERSION_3_0
//---------------------------------------------------------
//#if !defined(DADA_GL_CORE_VERSION_3_0) && defined(GL_VERSION_3_0)

extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

//#endif // VERSION_3_0




#endif // DADA_WITH_GLEW

namespace dada
{

class GL
{
public:
  enum Extension
  {
    ARB_vertex_array_object,

    EXTENSION_END
  };

  static bool init();
  static bool isSupported(Extension ext);

private:
  GL();
  GL(const GL&);

  static bool initCore();
  static bool initInfo();
  static bool initExtensions();

  static int m_major;
  static int m_minor;
  static const char* m_vendor;
  static const char* m_renderer;
  static const char* m_version;
  static const char* m_glsl_version;
  static const char* m_extensions;
  static bool m_exts[EXTENSION_END];
};

inline bool GL::isSupported(GL::Extension ext)
{
  return m_exts[ext];
}

} // dada

#endif // DADA_GL_GL_H
