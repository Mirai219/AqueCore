#pragma once

#include <cstdint>
#include <ostream>

namespace AQC {

    enum class MouseButton : uint8_t
    {
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        // Aliases
        Left = Button0,
        Right = Button1,
        Middle = Button2
    };

    inline std::ostream& operator<<(std::ostream& os, MouseButton button)
    {
        return os << static_cast<uint8_t>(button);
    }
}
