#include "ISmartShift.h"

using namespace HIDPP20;

ISmartShift::SmartshiftStatus ISmartShift::getStatus()
{
    auto results = call(GetStatus);
    return SmartshiftStatus
    {
        new bool(results[0]-1), // Active
        new uint8_t(results[1]), // AutoDisengage
        new uint8_t(results[2]) // Default AutoDisengage
    };
}

void ISmartShift::setStatus(SmartshiftStatus status)
{
    std::vector<uint8_t> params (3);

    params[0] = status.Active != nullptr ? *status.Active + 1 : 0;
    params[1] = status.AutoDisengage != nullptr ? *status.AutoDisengage : 0;
    params[2] = status.DefaultAutoDisengage != nullptr ? *status.DefaultAutoDisengage : 0;

    call(SetStatus, params);
}

ISmartShift::ISmartShift (Device *dev):
        FeatureInterface (dev, ID, "SmartShift")
{
}

