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

#include <functional>

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
	testIsFile();
}
}
}
