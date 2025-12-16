#pragma once

#include <cstdint>
#include <ostream>

namespace AQC {

    enum class KeyCode : uint16_t
    {
        None = 0,

        // --- Printable ---
        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,

        D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,

        Semicolon,
        Equal,

        A, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T,
        U, V, W, X, Y, Z,

        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,

        // --- Function ---
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,

        Right, Left, Down, Up,
        PageUp, PageDown,
        Home, End,

        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,

        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,
        F13, F14, F15, F16, F17, F18,
        F19, F20, F21, F22, F23, F24, F25,

        KP0, KP1, KP2, KP3, KP4,
        KP5, KP6, KP7, KP8, KP9,
        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,
        KPEqual,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,
    };
    inline std::ostream& operator<<(std::ostream& os, KeyCode key)
    {
        return os << static_cast<uint16_t>(key);
    }
}
