#ifndef _NS_GRAPHICS_CORE_GPU_GL_COMMON_H_
#define _NS_GRAPHICS_CORE_GPU_GL_COMMON_H_

#include "common/common.h"


#if defined(__APPLE__) || defined(__MACH__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#endif

#define GLCHECK(x)                                 \
	x;                                             \
	do                                             \
	{                                              \
		GLenum glError = glGetError();             \
		if (glError != GL_NO_ERROR)                \
		{                                          \
			NS_ERROR("glGetError(): {}", glError); \
			assert(0);                             \
		}                                          \
	} while (0)

#endif