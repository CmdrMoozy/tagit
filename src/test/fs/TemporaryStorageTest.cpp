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

#include "TemporaryStorageTest.h"

#include <string>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/TemporaryStorage.h"

namespace
{
void testTemporaryFile()
{
	boost::filesystem::path path;

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::FILE);
		path = temp.getPath();
		vrfy::assert::assertTrue(boost::filesystem::exists(path));
		vrfy::assert::assertTrue(
		        boost::filesystem::is_regular_file(path));
	}

	vrfy::assert::assertFalse(boost::filesystem::exists(path));
}

void testTemporaryDirectory()
{
	boost::filesystem::path path;

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::DIRECTORY);
		path = temp.getPath();
		vrfy::assert::assertTrue(boost::filesystem::exists(path));
		vrfy::assert::assertTrue(boost::filesystem::is_directory(path));
	}

	vrfy::assert::assertFalse(boost::filesystem::exists(path));
}
}

namespace tagit_test
{
namespace fs
{
void TemporaryStorageTest::test()
{
	testTemporaryFile();
	testTemporaryDirectory();
}
}
}
