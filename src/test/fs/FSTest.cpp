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

#include "FSTest.h"

#include <fstream>
#include <functional>
#include <sstream>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/FS.h"
#include "tagitcommon/fs/TemporaryStorage.h"

namespace
{
void testStripSymlink()
{
	tagit::fs::TemporaryStorage temp(
	        tagit::fs::TemporaryStorageType::DIRECTORY);
	boost::filesystem::path rootPath(temp.getPath());
	boost::filesystem::path filePath = rootPath / "file";
	boost::filesystem::path symlinkPath = rootPath / "symlink";

	tagit::fs::createFile(filePath.string());
	tagit::fs::createSymlink(filePath.string(), symlinkPath.string());

	std::string resolved = tagit::fs::stripSymlink(symlinkPath.string());
	vrfy::assert::assertEquals(symlinkPath.string(), resolved);
}

void testCreateFile()
{
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);
	vrfy::assert::assertTrue(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	vrfy::assert::assertNoThrow(
	        [&temp]()
	        {
		        boost::filesystem::remove(
		                boost::filesystem::path(temp.getPath()));
		});
	tagit::fs::createFile(temp.getPath());
	vrfy::assert::assertTrue(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	vrfy::assert::assertTrue(boost::filesystem::is_regular_file(
	        boost::filesystem::path(temp.getPath())));
}

void testCreateSymlink()
{
	tagit::fs::TemporaryStorage temp(
	        tagit::fs::TemporaryStorageType::DIRECTORY);
	boost::filesystem::path rootPath(temp.getPath());
	boost::filesystem::path filePath = rootPath / "file";
	boost::filesystem::path symlinkPath = rootPath / "symlink";

	tagit::fs::createFile(filePath.string());
	tagit::fs::createSymlink(filePath.string(), symlinkPath.string());

	vrfy::assert::assertTrue(boost::filesystem::exists(filePath));
	vrfy::assert::assertTrue(boost::filesystem::is_regular_file(filePath));
	vrfy::assert::assertTrue(boost::filesystem::exists(symlinkPath));
	vrfy::assert::assertTrue(boost::filesystem::is_symlink(symlinkPath));
}

void testGetSize()
{
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);

	for(int i = 1; i <= 10; ++i)
	{
		std::ostringstream oss;
		for(int v = 0; v < i * 100; ++v)
			oss << v;
		oss.flush();
		std::string contents = oss.str();
		std::size_t expected = static_cast<std::size_t>(oss.tellp());
		vrfy::assert::assertEquals(expected, contents.length());

		std::ofstream out(temp.getPath(),
		                  std::ios_base::out | std::ios_base::binary |
		                          std::ios_base::trunc);
		vrfy::assert::assertTrue(out.is_open());
		out.write(contents.c_str(),
		          static_cast<std::streamsize>(contents.length()));
		out.flush();
		out.close();

		vrfy::assert::assertEquals(expected,
		                           tagit::fs::getSize(temp.getPath()));
	}
}

void testGetMode()
{
	auto test = [](const tagit::fs::TemporaryStorage &temp, uintmax_t mode)
	{
		int ret = chmod(temp.getPath().c_str(),
		                static_cast<mode_t>(mode));
		vrfy::assert::assertEquals(0, ret);
		vrfy::assert::assertEquals(mode,
		                           tagit::fs::getMode(temp.getPath()));
	};

	std::string path;

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::FILE);
		path = temp.getPath();

		test(temp, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		test(temp,
		     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		test(temp, S_IRUSR);
	}

	vrfy::assert::assertFalse(
	        boost::filesystem::exists(boost::filesystem::path(path)));
}

void testIsFile()
{
	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::FILE);
		vrfy::assert::assertTrue(tagit::fs::isFile(temp.getPath()));
	}

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::DIRECTORY);
		vrfy::assert::assertFalse(tagit::fs::isFile(temp.getPath()));
	}
}

void testIsExecutable()
{
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);

	vrfy::assert::assertTrue(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	vrfy::assert::assertFalse(tagit::fs::isExecutable(temp.getPath()));

	struct stat stats;
	int ret = stat(temp.getPath().c_str(), &stats);
	vrfy::assert::assertEquals(0, ret);

	ret = chmod(temp.getPath().c_str(),
	            tagit::fs::getMode(temp.getPath()) | S_IXUSR);
	vrfy::assert::assertEquals(0, ret);

	vrfy::assert::assertTrue(tagit::fs::isExecutable(temp.getPath()));
}
}

namespace tagit_test
{
namespace fs
{
void FSTest::test()
{
	testStripSymlink();
	testCreateFile();
	testCreateSymlink();
	testGetSize();
	testGetMode();
	testIsFile();
	testIsExecutable();
}
}
}
