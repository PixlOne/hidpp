/*
 * Copyright 2019 PixlOne
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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