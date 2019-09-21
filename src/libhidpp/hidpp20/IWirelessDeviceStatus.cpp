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
#include "IWirelessDeviceStatus.h"

using namespace HIDPP20;

IWirelessDeviceStatus::Status IWirelessDeviceStatus::statusBroadcastEvent (const HIDPP::Report &event)
{
    assert (event.function () == StatusBroadcast);
    Status status = {};
    auto params = event.parameterBegin();
    status.Reconnection = params[0];
    status.ReconfNeeded = params[1];
    status.PowerSwitch = params[2];
    return status;
}

IWirelessDeviceStatus::IWirelessDeviceStatus (Device *dev):
        FeatureInterface (dev, ID, "WirelessDeviceStatus")
{
}