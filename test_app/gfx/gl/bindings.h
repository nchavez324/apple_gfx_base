#ifndef TEST_APP_GFX_GL_BINDINGS_H
#define TEST_APP_GFX_GL_BINDINGS_H

#include "test_app/common/platform_defines.h"

#if TARGET_OS_OSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#elif TARGET_OS_IPHONE
#ifdef __OBJC__
#include <OpenGLES/EAGL.h>
#endif  // __OBJC__
// https://developer.apple.com/library/archive/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/AdoptingOpenGLES3/AdoptingOpenGLES3.html
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#endif  // TARGET_OS_IPHONE

// #if defined(_WIN32) || defined(_WIN64)
// #include <windows.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <gl/glew.h>

// if defined (__ANDROID__) || defined(ANDROID)
// #include <GLES2/gl2.h>
// #include <GLES2/gl2ext.h>

// #if defined(__linux__) || defined(__unix__) || defined(__posix__)
// #include <GL/gl.h>
// #include <GL/glext.h>
// #include <GL/glu.h>

static inline const char *GetGLErrorString(GLenum error) {
  const char *str;
  switch (error) {
    case GL_NO_ERROR:
      str = "GL_NO_ERROR";
      break;
    case GL_INVALID_ENUM:
      str = "GL_INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      str = "GL_INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      str = "GL_INVALID_OPERATION";
      break;
    case GL_OUT_OF_MEMORY:
      str = "GL_OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      str = "GL_INVALID_FRAMEBUFFER_OPERATION";
      break;
#if defined __gl_h_
    case GL_STACK_OVERFLOW:
      str = "GL_STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      str = "GL_STACK_UNDERFLOW";
      break;
    case GL_TABLE_TOO_LARGE:
      str = "GL_TABLE_TOO_LARGE";
      break;
#endif
    default:
      str = "(ERROR: Unknown Error Enum)";
      break;
  }
  return str;
}

#define GetGLError()                                                                            \
  {                                                                                             \
    GLenum err = glGetError();                                                                  \
    while (err != GL_NO_ERROR) {                                                                \
      NSLog(@"GLError %s set in File:%s Line:%d\n", GetGLErrorString(err), __FILE__, __LINE__); \
      err = glGetError();                                                                       \
    }                                                                                           \
  }

#define GetGLErrorCpp()                                                               \
  {                                                                                   \
    GLenum err = glGetError();                                                        \
    while (err != GL_NO_ERROR) {                                                      \
      std::cout << "GLError" << GetGLErrorString(err) << " set in File: " << __FILE__ \
                << " Line:" << __LINE__ << std::endl;                                 \
      err = glGetError();                                                             \
    }                                                                                 \
  }

#endif  // TEST_APP_GFX_GL_BINDINGS_H
