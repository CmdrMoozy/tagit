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

#include <sys/stat.h>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/Environment.h"
#include "tagitcommon/fs/FS.h"
#include "tagitcommon/fs/TemporaryStorage.h"
#include "tagitcommon/util/ScopeExit.h"

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

void testWhich()
{
	tagit::fs::TemporaryStorage temp(
	        tagit::fs::TemporaryStorageType::DIRECTORY);
	boost::filesystem::path pathObj(temp.getPath());
	boost::filesystem::path a = pathObj / "a";
	boost::filesystem::create_directory(a);
	boost::filesystem::path b = pathObj / "b";
	boost::filesystem::create_directory(b);

	const std::string oldPath(getenv("PATH"));
	tagit::util::ScopeExit cleanup(
	        [oldPath]()
	        {
		        int ret = setenv("PATH", oldPath.c_str(), 1);
		        vrfy::assert::assertEquals(0, ret);
		});

	{
		std::ostringstream oss;
		oss << a.string() << ":" << b.string();
		int ret = setenv("PATH", oss.str().c_str(), 1);
		vrfy::assert::assertEquals(0, ret);
	}

	boost::filesystem::path aDir = a / "foo";
	boost::filesystem::create_directory(aDir);
	boost::filesystem::path bExe1 = b / "foo";
	tagit::fs::createFile(bExe1.string());
	int ret = chmod(bExe1.string().c_str(),
	                tagit::fs::getMode(bExe1.string()) | S_IXUSR);
	vrfy::assert::assertEquals(0, ret);
	auto which = tagit::fs::which("foo");
	vrfy::assert::assertTrue(!!which);
	vrfy::assert::assertEquals(bExe1.string(), *which);

	boost::filesystem::path aNonExe = a / "bar";
	tagit::fs::createFile(aNonExe.string());
	boost::filesystem::path bExe2 = b / "bar";
	tagit::fs::createFile(bExe2.string());
	ret = chmod(bExe2.string().c_str(),
	            tagit::fs::getMode(bExe2.string()) | S_IXUSR);
	vrfy::assert::assertEquals(0, ret);
	which = tagit::fs::which("bar");
	vrfy::assert::assertTrue(!!which);
	vrfy::assert::assertEquals(bExe2.string(), *which);
}
}

namespace tagit_test
{
namespace fs
{
void EnvironmentTest::test()
{
	testGetSystemPath();
	testWhich();
}
}
}
