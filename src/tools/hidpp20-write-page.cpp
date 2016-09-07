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

#include <cstdio>

extern "C" {
#include <unistd.h>
}

#include <hidpp20/Device.h>
#include <hidpp20/Error.h>
#include <hidpp20/IOnboardProfiles.h>

#include "common/common.h"
#include "common/Option.h"
#include "common/CommonOptions.h"

int main (int argc, char *argv[])
{
	static const char *args = "/dev/hidrawX page";
	HIDPP::DeviceIndex device_index = HIDPP::DefaultDevice;

	std::vector<Option> options = {
		DeviceIndexOption (device_index),
		VerboseOption (),
	};
	Option help = HelpOption (argv[0], args, &options);
	options.push_back (help);

	int first_arg;
	if (!Option::processOptions (argc, argv, options, first_arg))
		return EXIT_FAILURE;

	if (argc-first_arg != 2) {
		fprintf (stderr, "%s", getUsage (argv[0], args, &options).c_str ());
		return EXIT_FAILURE;
	}

	const char *path = argv[first_arg];
	char *end;
	int page = strtol (argv[first_arg+1], &end, 0);
	if (*end != '\0') {
		fprintf (stderr, "Page index must be a number.\n");
		return EXIT_FAILURE;
	}
	if (page < 0) {
		fprintf (stderr, "Page index must be positive.\n");
		return EXIT_FAILURE;
	}

	HIDPP20::Device dev (path, device_index);
	HIDPP20::IOnboardProfiles iop (&dev);
	auto desc = iop.getDescription ();

	if (page >= desc.sector_count) {
		fprintf (stderr, "Page index too big: page count is %d.\n", desc.sector_count);
		return EXIT_FAILURE;
	}

	iop.memoryAddrWrite (page, 0);

	std::size_t r = 0;
	std::vector<uint8_t> data (16);
	while (r < desc.sector_size) {
		int ret = read (0, data.data (), data.size ());
		if (ret == -1) {
			perror ("read");
			return EXIT_FAILURE;
		}
		if (ret == 0) {
			break;
		}
		iop.memoryWrite (data);
		r += ret;
	}

	try {
		iop.memoryWriteEnd ();
	}
	catch (HIDPP20::Error e) {
		if (e.errorCode () == HIDPP20::Error::HWError) {
			fprintf (stderr, "memoryWriteEnd returned Hardware Error, maybe the CRC in wrong but the page is actually written.\n");
		}
		else throw e;
	}

	return EXIT_SUCCESS;
}