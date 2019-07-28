#ifndef HIDPP_IHIRESSCROLL_H
#define HIDPP_IHIRESSCROLL_H

#include <hidpp20/FeatureInterface.h>

namespace HIDPP20
{
    class IHiresScroll : public FeatureInterface
    {
    public:
        static constexpr uint16_t ID = 0x2121;

        enum Function
        {
            GetCapabilities = 0,
            GetMode = 1,
            SetMode = 2,
            GetRatchetState = 3
        };

        enum Event {
            WheelMovement = 0,
            RatchetSwitch = 1,
        };

        enum Capability : uint8_t
        {
            Invertable = 1<<3,
            HasRatchet = 1<<2
        };

        enum Mode : uint8_t
        {
            Inverted = 1<<2,
            HiRes = 1<<1,
            Target = 1
        };

        enum RatchetState : uint8_t
        {
            FreeWheel = 0,
            Ratchet = 1
        };

        struct Capabilities
        {
            uint8_t Multiplier;
            uint8_t Flags;
        };

        struct WheelStatus
        {
            bool HiRes;
            uint8_t periods;
            uint16_t deltaV;
        };

        Capabilities getCapabilities();

        uint8_t getMode();

        void setMode(uint8_t mode);

        bool getRatchetState();

        static WheelStatus wheelMovementEvent (const HIDPP::Report &event);

        static RatchetState ratchetSwitchEvent (const HIDPP::Report &event);

        IHiresScroll(Device* dev);
    };
}

#endif //HIDPP_IHIRESSCROLL_H
