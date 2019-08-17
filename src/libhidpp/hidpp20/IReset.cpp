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

#include "IReset.h"

using namespace HIDPP20;

uint16_t IReset::getProfile()
{
    auto results = call(GetProfile);
    return (results[0] << 8) | results[1];
}

void IReset::reset (uint16_t profile)
{
    std::vector<uint8_t> params;
    params.push_back((uint8_t)(profile >> 8));
    params.push_back((uint8_t)(profile & 0xFF));

    call(Reset, params);
}

IReset::IReset (Device *dev):
        FeatureInterface (dev, ID, "Reset")
{
}