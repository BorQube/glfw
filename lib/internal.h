//========================================================================
// GLFW - An OpenGL framework
// Platform:    Any
// API version: 3.0
// WWW:         http://www.glfw.org/
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#ifndef _internal_h_
#define _internal_h_

//========================================================================
// GLFWGLOBAL is a macro that places all global variables in the init.c
// module (all other modules reference global variables as 'extern')
//========================================================================

#if defined(_init_c_)
#define GLFWGLOBAL
#else
#define GLFWGLOBAL extern
#endif


//========================================================================
// Input handling definitions
//========================================================================

// Internal key and button state/action definitions
#define GLFW_STICK 2


//------------------------------------------------------------------------
// Platform specific definitions goes in platform.h (which also includes
// glfw.h)
//------------------------------------------------------------------------

#include "platform.h"


//------------------------------------------------------------------------
// Window opening hints (set by glfwOpenWindowHint)
// A bucket of semi-random stuff bunched together for historical reasons
// This is used only by the platform independent code and only to store
// parameters passed to us by glfwOpenWindowHint
//------------------------------------------------------------------------
typedef struct {
    int         refreshRate;
    int         accumRedBits;
    int         accumGreenBits;
    int         accumBlueBits;
    int         accumAlphaBits;
    int         auxBuffers;
    int         stereo;
    int         windowNoResize;
    int         samples;
    int         glMajor;
    int         glMinor;
    int         glForward;
    int         glDebug;
    int         glProfile;
} _GLFWhints;


//------------------------------------------------------------------------
// Parameters relating to the creation of the context and window but not
// directly related to the properties of the framebuffer
// This is used to pass window and context creation parameters from the
// platform independent code to the platform specific code
//------------------------------------------------------------------------
typedef struct {
    int         mode;
    int         refreshRate;
    int         windowNoResize;
    int         glMajor;
    int         glMinor;
    int         glForward;
    int         glDebug;
    int         glProfile;
} _GLFWwndconfig;


//------------------------------------------------------------------------
// Framebuffer configuration descriptor, i.e. buffers and their sizes
// Also a platform specific ID used to map back to the actual backend APIs
// This is used to pass framebuffer parameters from the platform independent
// code to the platform specific code, and also to enumerate and select
// available framebuffer configurations
//------------------------------------------------------------------------
typedef struct {
    int         redBits;
    int         greenBits;
    int         blueBits;
    int         alphaBits;
    int         depthBits;
    int         stencilBits;
    int         accumRedBits;
    int         accumGreenBits;
    int         accumBlueBits;
    int         accumAlphaBits;
    int         auxBuffers;
    int         stereo;
    int         samples;
    GLFWintptr  platformID;
} _GLFWfbconfig;


//------------------------------------------------------------------------
// Window structure
//------------------------------------------------------------------------
typedef struct _GLFWwindow {

    // User callback functions
    GLFWwindowsizefun    windowSizeCallback;
    GLFWwindowclosefun   windowCloseCallback;
    GLFWwindowrefreshfun windowRefreshCallback;
    GLFWmousebuttonfun   mouseButtonCallback;
    GLFWmouseposfun      mousePosCallback;
    GLFWmousewheelfun    mouseWheelCallback;
    GLFWkeyfun           keyCallback;
    GLFWcharfun          charCallback;

    // User selected window settings
    int       mode;
    GLboolean sysKeysDisabled; // System keys disabled flag
    GLboolean windowNoResize;  // Resize- and maximize gadgets disabled flag
    int       refreshRate;     // Vertical monitor refresh rate

    // Input
    GLboolean stickyKeys;
    GLboolean stickyMouseButtons;
    GLboolean keyRepeat;
    int       mousePosX, mousePosY;
    int       wheelPos;
    char      mouseButton[GLFW_MOUSE_BUTTON_LAST + 1];
    char      key[GLFW_KEY_LAST + 1];
    int       lastChar;

    // Window status & parameters
    GLboolean active;          // Application active flag
    GLboolean iconified;       // Window iconified flag
    int       width, height;   // Window width and heigth
    GLboolean accelerated;     // GL_TRUE if window is HW accelerated

    // Framebuffer attributes
    int       redBits;
    int       greenBits;
    int       blueBits;
    int       alphaBits;
    int       depthBits;
    int       stencilBits;
    int       accumRedBits;
    int       accumGreenBits;
    int       accumBlueBits;
    int       accumAlphaBits;
    int       auxBuffers;
    GLboolean stereo;
    int       samples;

    // OpenGL extensions and context attributes
    int       glMajor, glMinor, glRevision;
    int       glForward, glDebug, glProfile;

    PFNGLGETSTRINGIPROC GetStringi;

    _GLFW_PLATFORM_WINDOW_STATE;
} _GLFWwindow;


//------------------------------------------------------------------------
// Library global data
//------------------------------------------------------------------------
typedef struct {
    _GLFWhints   hints;
    _GLFWwindow* window;
    _GLFWwindow* currentWindow;
    _GLFWwindow* cursorLockWindow;

    _GLFW_PLATFORM_LIBRARY_STATE;
} _GLFWlibrary;


//========================================================================
// System independent global variables (GLFW internals)
//========================================================================

// Flag indicating if GLFW has been initialized
#if defined(_init_c_)
int _glfwInitialized = 0;
#else
GLFWGLOBAL int _glfwInitialized;
#endif

GLFWGLOBAL _GLFWlibrary _glfwLibrary;


//========================================================================
// Prototypes for platform specific implementation functions
//========================================================================

// Init/terminate
int _glfwPlatformInit(void);
int _glfwPlatformTerminate(void);

// Enable/Disable
void _glfwPlatformEnableSystemKeys(_GLFWwindow* window);
void _glfwPlatformDisableSystemKeys(_GLFWwindow* window);

// Fullscreen
int  _glfwPlatformGetVideoModes(GLFWvidmode* list, int maxcount);
void _glfwPlatformGetDesktopMode(GLFWvidmode* mode);

// Joystick
int _glfwPlatformGetJoystickParam(int joy, int param);
int _glfwPlatformGetJoystickPos(int joy, float* pos, int numaxes);
int _glfwPlatformGetJoystickButtons(int joy, unsigned char* buttons, int numbuttons);

// Time
double _glfwPlatformGetTime(void);
void _glfwPlatformSetTime(double time);

// Window management
int  _glfwPlatformOpenWindow(_GLFWwindow* window, int width, int height, const _GLFWwndconfig* wndconfig, const _GLFWfbconfig* fbconfig);
int  _glfwPlatformMakeWindowCurrent(_GLFWwindow* window);
void _glfwPlatformCloseWindow(_GLFWwindow* window);
void _glfwPlatformSetWindowTitle(_GLFWwindow* window, const char* title);
void _glfwPlatformSetWindowSize(_GLFWwindow* window, int width, int height);
void _glfwPlatformSetWindowPos(_GLFWwindow* window, int x, int y);
void _glfwPlatformIconifyWindow(_GLFWwindow* window);
void _glfwPlatformRestoreWindow(_GLFWwindow* window);
void _glfwPlatformHideMouseCursor(_GLFWwindow* window);
void _glfwPlatformShowMouseCursor(_GLFWwindow* window);
void _glfwPlatformSetMouseCursorPos(_GLFWwindow* window, int x, int y);

// Event management
void _glfwPlatformPollEvents(void);
void _glfwPlatformWaitEvents(void);

// OpenGL context management
void _glfwPlatformSwapBuffers(void);
void _glfwPlatformSwapInterval(int interval);
void _glfwPlatformRefreshWindowParams(void);
int  _glfwPlatformExtensionSupported(const char* extension);
void* _glfwPlatformGetProcAddress(const char* procname);


//========================================================================
// Prototypes for platform independent internal functions
//========================================================================

// Window management (window.c)
void _glfwClearWindowHints(void);

// Input handling (window.c)
void _glfwClearInput(_GLFWwindow* window);
void _glfwInputDeactivation(_GLFWwindow* window);
void _glfwInputKey(_GLFWwindow* window, int key, int action);
void _glfwInputChar(_GLFWwindow* window, int character, int action);
void _glfwInputMouseClick(_GLFWwindow* window, int button, int action);

// OpenGL extensions (glext.c)
void _glfwParseGLVersion(int* major, int* minor, int* rev);
int _glfwStringInExtensionString(const char* string, const GLubyte* extensions);

// Framebuffer configs
const _GLFWfbconfig* _glfwChooseFBConfig(const _GLFWfbconfig* desired,
                                         const _GLFWfbconfig* alternatives,
                                         unsigned int count);


#endif // _internal_h_