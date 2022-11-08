#ifndef TEST_APP_COMMON_GRAPHICS_DEFINES_H
#define TEST_APP_COMMON_GRAPHICS_DEFINES_H

#if defined(_GFX_METAL) && _GFX_METAL
#define GFX_METAL 1
#define GFX_GL 0
#define GFX_OPEN_GL 0
#define GFX_OPEN_GLES 0
#define GFX_VULKAN 0

#elif defined(_GFX_OPEN_GL) && _GFX_OPEN_GL
#define GFX_METAL 0
#define GFX_GL 1
#define GFX_OPEN_GL 1
#define GFX_OPEN_GLES 0
#define GFX_VULKAN 0

#elif defined(_GFX_OPEN_GLES) && _GFX_OPEN_GLES
#define GFX_METAL 0
#define GFX_GL 1
#define GFX_OPEN_GL 0
#define GFX_OPEN_GLES 1
#define GFX_VULKAN 0

#elif defined(_GFX_VULKAN) && _GFX_VULKAN
#define GFX_METAL 0
#define GFX_GL 0
#define GFX_OPEN_GL 0
#define GFX_OPEN_GLES 0
#define GFX_VULKAN 1

#else
#define GFX_METAL 0
#define GFX_GL 0
#define GFX_OPEN_GL 0
#define GFX_OPEN_GLES 0
#define GFX_VULKAN 0

#endif

#endif  // TEST_APP_COMMON_GRAPHICS_DEFINES_H
