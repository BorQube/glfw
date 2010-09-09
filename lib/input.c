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

#include "internal.h"


//========================================================================
// 
//========================================================================

GLFWAPI int glfwGetKey(GLFWwindow window, int key)
{
    if (!_glfwInitialized)
        return GLFW_RELEASE;

    // Is it a valid key?
    if (key < 0 || key > GLFW_KEY_LAST)
        return GLFW_RELEASE;

    if (window->key[key] == GLFW_STICK)
    {
        // Sticky mode: release key now
        window->key[key] = GLFW_RELEASE;
        return GLFW_PRESS;
    }

    return (int) window->key[key];
}


//========================================================================
// 
//========================================================================

GLFWAPI int glfwGetMouseButton(GLFWwindow window, int button)
{
    if (!_glfwInitialized)
        return GLFW_RELEASE;

    // Is it a valid mouse button?
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        return GLFW_RELEASE;

    if (window->mouseButton[button] == GLFW_STICK)
    {
        // Sticky mode: release mouse button now
        window->mouseButton[button] = GLFW_RELEASE;
        return GLFW_PRESS;
    }

    return (int) window->mouseButton[button];
}


//========================================================================
// 
//========================================================================

GLFWAPI void glfwGetMousePos(GLFWwindow window, int* xpos, int* ypos)
{
    if (!_glfwInitialized)
        return;

    // Return mouse position
    if (xpos != NULL)
        *xpos = window->mousePosX;

    if (ypos != NULL)
        *ypos = window->mousePosY;
}


//========================================================================
// 
//========================================================================

GLFWAPI void glfwSetMousePos(GLFWwindow window, int xpos, int ypos)
{
    if (!_glfwInitialized)
        return;

    // Don't do anything if the mouse position did not change
    if (xpos == window->mousePosX && ypos == window->mousePosY)
        return;

    // Set GLFW mouse position
    window->mousePosX = xpos;
    window->mousePosY = ypos;

    // If we have a locked mouse, do not change cursor position
    if (_glfwLibrary.cursorLockWindow)
        return;

    // Update physical cursor position
    _glfwPlatformSetMouseCursorPos(window, xpos, ypos);
}


//========================================================================
// 
//========================================================================

GLFWAPI int glfwGetMouseWheel(GLFWwindow window)
{
    if (!_glfwInitialized)
        return 0;

    return window->wheelPos;
}


//========================================================================
// 
//========================================================================

GLFWAPI void glfwSetMouseWheel(GLFWwindow window, int pos)
{
    if (!_glfwInitialized)
        return;

    window->wheelPos = pos;
}


//========================================================================
// Set callback function for keyboard input
//========================================================================

GLFWAPI void glfwSetKeyCallback(GLFWwindow window, GLFWkeyfun cbfun)
{
    if (!_glfwInitialized)
        return;

    window->keyCallback = cbfun;
}


//========================================================================
// Set callback function for character input
//========================================================================

GLFWAPI void glfwSetCharCallback(GLFWwindow window, GLFWcharfun cbfun)
{
    if (!_glfwInitialized)
        return;

    window->charCallback = cbfun;
}


//========================================================================
// Set callback function for mouse clicks
//========================================================================

GLFWAPI void glfwSetMouseButtonCallback(GLFWwindow window, GLFWmousebuttonfun cbfun)
{
    if (!_glfwInitialized)
        return;

    window->mouseButtonCallback = cbfun;
}


//========================================================================
// Set callback function for mouse moves
//========================================================================

GLFWAPI void glfwSetMousePosCallback(GLFWwindow window, GLFWmouseposfun cbfun)
{
    if (!_glfwInitialized || !_glfwLibrary.window)
        return;

    // Set callback function
    _glfwLibrary.window->mousePosCallback = cbfun;

    // Call the callback function to let the application know the current
    // mouse position
    if (cbfun)
        cbfun(window->mousePosX, window->mousePosY);
}


//========================================================================
// Set callback function for mouse wheel
//========================================================================

GLFWAPI void glfwSetMouseWheelCallback(GLFWwindow window, GLFWmousewheelfun cbfun)
{
    if (!_glfwInitialized)
        return;

    // Set callback function
    window->mouseWheelCallback = cbfun;

    // Call the callback function to let the application know the current
    // mouse wheel position
    if (cbfun)
        cbfun(window->wheelPos);
}
