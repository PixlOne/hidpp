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
    auto current_status = getStatus();
    std::vector<uint8_t> params (3);

    if(status.Active == nullptr) params.push_back(*current_status.Active);
    else params.push_back(*status.Active);

    if(status.AutoDisengage == nullptr) params.push_back(*current_status.AutoDisengage);
    else params.push_back(*status.AutoDisengage);

    if(status.AutoDisengage == nullptr) params.push_back(*current_status.DefaultAutoDisengage);
    else params.push_back(*status.DefaultAutoDisengage);

    call(SetStatus, params);
}

ISmartShift::ISmartShift (Device *dev):
        FeatureInterface (dev, ID, "SmartShift")
{
}

