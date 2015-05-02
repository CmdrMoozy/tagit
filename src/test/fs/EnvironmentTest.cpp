/*
 * TagIt - An app for transcoding, tagging, and organizing media files.
 * Copyright (C) 2015  Axel Rasmussen
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
 */

#include "EnvironmentTest.h"

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "tagitcommon/fs/Environment.h"

namespace
{
void testGetSystemPath()
{
	const std::string EXPECTED_PATH =
	        "/usr/local/bin:/usr/bin:/bin:"
	        "/opt/bin:/usr/x86_64-pc-linux-gnu/gcc-bin/4.9.2:"
	        "/opt/android-sdk-update-manager/tools:"
	        "/opt/android-sdk-update-manager/platform-tools";

	const std::vector<std::string> EXPECTED_COMPONENTS(
	        {"/usr/local/bin", "/usr/bin", "/bin", "/opt/bin",
	         "/usr/x86_64-pc-linux-gnu/gcc-bin/4.9.2",
	         "/opt/android-sdk-update-manager/tools",
	         "/opt/android-sdk-update-manager/platform-tools"});

	int ret = setenv("PATH", EXPECTED_PATH.c_str(), 1);
	vrfy::assert::assertEquals(true, ret == 0);

	std::vector<std::string> components = tagit::fs::getSystemPath();
	vrfy::assert::assertEquals(EXPECTED_COMPONENTS.size(),
	                           components.size());
	for(std::size_t i = 0; i < components.size(); ++i)
	{
		vrfy::assert::assertEquals(components[i],
		                           EXPECTED_COMPONENTS[i]);
	}
}
}

namespace tagit_test
{
namespace fs
{
void EnvironmentTest::test()
{
	testGetSystemPath();
}
}
}
