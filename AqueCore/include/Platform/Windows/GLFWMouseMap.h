#pragma once

#include <GLFW/glfw3.h>
#include "AqueCore/MouseButtonCodes.h"

namespace AQC {

    inline MouseButton GLFWMouseButtonToAqure(int button)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:   return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT:  return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;

        case GLFW_MOUSE_BUTTON_4: return MouseButton::Button3;
        case GLFW_MOUSE_BUTTON_5: return MouseButton::Button4;
        case GLFW_MOUSE_BUTTON_6: return MouseButton::Button5;
        case GLFW_MOUSE_BUTTON_7: return MouseButton::Button6;
        case GLFW_MOUSE_BUTTON_8: return MouseButton::Button7;

        default:
            return MouseButton::Button0;
        }
    }
    inline int AqureMouseButtonToGLFW(MouseButton button)
    {
        switch (button)
        {
        case MouseButton::Left:   return GLFW_MOUSE_BUTTON_LEFT;
        case MouseButton::Right:  return GLFW_MOUSE_BUTTON_RIGHT;
        case MouseButton::Middle: return GLFW_MOUSE_BUTTON_MIDDLE;

        case MouseButton::Button3: return GLFW_MOUSE_BUTTON_4;
        case MouseButton::Button4: return GLFW_MOUSE_BUTTON_5;
        case MouseButton::Button5: return GLFW_MOUSE_BUTTON_6;
        case MouseButton::Button6: return GLFW_MOUSE_BUTTON_7;
        case MouseButton::Button7: return GLFW_MOUSE_BUTTON_8;

        default:
            return GLFW_MOUSE_BUTTON_LEFT;
        }
    }
}
