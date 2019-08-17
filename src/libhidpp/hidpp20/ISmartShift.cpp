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

