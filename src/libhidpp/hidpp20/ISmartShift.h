#ifndef HIDPP_ISMARTSHIFT_H
#define HIDPP_ISMARTSHIFT_H

#include <hidpp20/FeatureInterface.h>

namespace HIDPP20
{
    class ISmartShift : public FeatureInterface
    {
    public:
        static constexpr uint16_t ID = 0x2110;

        enum Function
        {
            GetStatus = 0,
            SetStatus = 1
        };

        struct SmartshiftStatus
        {
            bool* Active = nullptr;
            uint8_t* AutoDisengage = nullptr;
            uint8_t* DefaultAutoDisengage = nullptr;
        };

        SmartshiftStatus getStatus();

        void setStatus(SmartshiftStatus status);

        ISmartShift(Device *dev);
    };
}

#endif //HIDPP_ISMARTSHIFT_H
