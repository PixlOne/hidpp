#include <cassert>
#include "IHiresScroll.h"

using namespace HIDPP20;

IHiresScroll::Capabilities IHiresScroll::getCapabilities ()
{
    auto results = call(GetCapabilities);
    return Capabilities
    {
        results[0], // Multiplier
        results[1]  // Flags
    };
}

uint8_t IHiresScroll::getMode ()
{
    auto results = call(GetMode);
    return results[0];
}

void IHiresScroll::setMode (uint8_t mode)
{
    std::vector<uint8_t> params (1);
    params[0] = mode;

    call(SetMode, params);
}

bool IHiresScroll::getRatchetState ()
{
    auto results = call(GetRatchetState);
    return bool(results[0]);
}

IHiresScroll::WheelStatus IHiresScroll::wheelMovementEvent (const HIDPP::Report &event)
{
    assert (event.function () == WheelMovement);
    WheelStatus ws = {};
    auto params = event.parameterBegin();
    ws.HiRes = bool(params[0] & (1<<4));
    ws.periods = params[0] & 0x0F;
    ws.deltaV = params[1] << 8 | params[2];
    return ws;
}

IHiresScroll::RatchetState IHiresScroll::ratchetSwitchEvent (const HIDPP::Report &event)
{
    assert (event.function () == RatchetSwitch);
    auto params = event.parameterBegin();
    return (RatchetState)params[0];
}

IHiresScroll::IHiresScroll (Device *dev):
        FeatureInterface (dev, ID, "HiresScroll")
{
}