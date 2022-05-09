#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <cstdint>
#include <vector>

namespace sn
{
    using Byte = std::uint8_t;
    class Controller
    {
    public:
        Controller();
        enum Buttons
        {
            A,
            B,
            Select,
            Start,
            Up,
            Down,
            Left,
            Right,
            TotalButtons,
        };

        void strobe(Byte b);
        Byte read();
    private:
        bool m_strobe;
        unsigned int m_keyStates;
    };
}

#endif // CONTROLLER_H