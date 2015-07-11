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

#include <catch/catch.hpp>

#include <fstream>
#include <functional>
#include <sstream>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/FS.h"
#include "tagitcommon/fs/TemporaryStorage.h"

TEST_CASE("Test symlink stripping", "[fs]")
{
	tagit::fs::TemporaryStorage temp(
	        tagit::fs::TemporaryStorageType::DIRECTORY);
	boost::filesystem::path rootPath(temp.getPath());
	boost::filesystem::path filePath = rootPath / "file";
	boost::filesystem::path symlinkPath = rootPath / "symlink";

	tagit::fs::createFile(filePath.string());
	tagit::fs::createSymlink(filePath.string(), symlinkPath.string());

	std::string resolved = tagit::fs::stripSymlink(symlinkPath.string());
	CHECK(symlinkPath.string() == resolved);
}

TEST_CASE("Test file creation", "[fs]")
{
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);
	CHECK(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	CHECK_NOTHROW(boost::filesystem::remove(
	        boost::filesystem::path(temp.getPath())));
	tagit::fs::createFile(temp.getPath());
	CHECK(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	CHECK(boost::filesystem::is_regular_file(
	        boost::filesystem::path(temp.getPath())));
}

TEST_CASE("Test symlink creation", "[fs]")
{
	tagit::fs::TemporaryStorage temp(
	        tagit::fs::TemporaryStorageType::DIRECTORY);
	boost::filesystem::path rootPath(temp.getPath());
	boost::filesystem::path filePath = rootPath / "file";
	boost::filesystem::path symlinkPath = rootPath / "symlink";

	tagit::fs::createFile(filePath.string());
	tagit::fs::createSymlink(filePath.string(), symlinkPath.string());

	CHECK(boost::filesystem::exists(filePath));
	CHECK(boost::filesystem::is_regular_file(filePath));
	CHECK(boost::filesystem::exists(symlinkPath));
	CHECK(boost::filesystem::is_symlink(symlinkPath));
}

TEST_CASE("Test file size retrieval", "[fs]")
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
		CHECK(expected == contents.length());

		std::ofstream out(temp.getPath(),
		                  std::ios_base::out | std::ios_base::binary |
		                          std::ios_base::trunc);
		CHECK(out.is_open());
		out.write(contents.c_str(),
		          static_cast<std::streamsize>(contents.length()));
		out.flush();
		out.close();

		CHECK(expected == tagit::fs::getSize(temp.getPath()));
	}
}

TEST_CASE("Test file permissions retrieval", "[fs]")
{
	auto test = [](const tagit::fs::TemporaryStorage &temp, uintmax_t mode)
	{
		int ret = chmod(temp.getPath().c_str(),
		                static_cast<mode_t>(mode));
		CHECK(0 == ret);
		CHECK(mode == tagit::fs::getMode(temp.getPath()));
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

	CHECK(!boost::filesystem::exists(boost::filesystem::path(path)));
}

TEST_CASE("Test file detection functionality", "[fs]")
{
	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::FILE);
		CHECK(tagit::fs::isFile(temp.getPath()));
	}

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::DIRECTORY);
		CHECK(!tagit::fs::isFile(temp.getPath()));
	}
}

TEST_CASE("Test executable detection functionality", "[fs]")
{
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);

	CHECK(boost::filesystem::exists(
	        boost::filesystem::path(temp.getPath())));
	CHECK(!tagit::fs::isExecutable(temp.getPath()));

	struct stat stats;
	int ret = stat(temp.getPath().c_str(), &stats);
	CHECK(0 == ret);

	ret = chmod(temp.getPath().c_str(),
	            tagit::fs::getMode(temp.getPath()) | S_IXUSR);
	CHECK(0 == ret);

	CHECK(tagit::fs::isExecutable(temp.getPath()));
}
