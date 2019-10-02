/*
 * Copyright 2015 Clément Vuchener
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

#ifndef LIBHIDPP_HIDPP10_IRECEIVER_H
#define LIBHIDPP_HIDPP10_IRECEIVER_H

#include <cstdint>
#include <string>
#include "Device.h"

namespace HIDPP10
{

    class Device;

    class IReceiver
    {
    public:
        enum Command : uint8_t {
            SwitchAndKeepAlive = 0x80,
            GetPairedDevices = 0x81
        };

        enum InformationType: uint8_t {
            DeviceInformation = 0x20,
            ExtendedDeviceInformation = 0x30,
            DeviceName = 0x40,
        };

        enum DeviceType: uint8_t {
            Unknown = 0x00,
            Keyboard = 0x01,
            Mouse = 0x02,
            Numpad = 0x03,
            Presenter = 0x04,
            Trackball = 0x08,
            Touchpad = 0x09,
        };

        enum PowerSwitchLocation {
            Base = 0x1,
            TopCase = 0x2,
            TopRightCornerEdge = 0x3,
            Other = 0x4,
            TopLeftCorner = 0x5,
            BottomLeftCorner = 0x6,
            TopRightCorner = 0x7,
            BottomRightCorner = 0x8,
            TopEdge = 0x9,
            RightEdge = 0xA,
            LeftEdge = 0xB,
            BottomEdge = 0xC,
        };

        enum Event : uint8_t
        {
            DeviceUnpaired = 0x40,
            DevicePaired = 0x41,
            ConnectionStatus = 0x42,
            Error = 0x7F
        };

        static const std::vector<uint8_t> Events;

        enum ConnectionStatus : uint8_t
        {
            ConnectionEstablished = 0,
            LinkLoss = 1
        };

        enum class RFReport : uint8_t
        {
            StandardKeyboard = 1,
            Mouse = 2,
            Multimedia = 3,
            PowerKeys = 4,
            MediaCenter = 8,
            KeyboardLEDs = 14,
            ShortHIDPP = 16,
            LongHIDPP = 17
        };

        enum ErrorType : uint8_t
        {
            KeepAliveTimeout = 1
        };

        struct DevicePairedEvent
        {
            bool moreEvents;
            bool empty;
            uint16_t pid;
            std::vector<uint8_t> reportBitfield;
        };

        IReceiver (Device *dev);

        void getPairedDevices ();

        void getDeviceInformation (unsigned int device,
                                   uint8_t *destination_id,
                                   uint8_t *report_interval,
                                   uint16_t *wpid,
                                   DeviceType *type);
        void getDeviceExtendedInformation (unsigned int device,
                                           uint32_t *serial,
                                           uint32_t *report_types,
                                           PowerSwitchLocation *ps_loc);
        std::string getDeviceName (unsigned int device);

        static DevicePairedEvent devicePairedEvent (const HIDPP::Report &event);

        static uint8_t connectionStatusEvent (const HIDPP::Report &event);

        static uint8_t errorEvent (const HIDPP::Report &event);

    private:
        Device *_dev;
    };

}

#endif

