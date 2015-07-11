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

#include <string>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/TemporaryStorage.h"

TEST_CASE("Test temporary file functionality", "[fs]")
{
	boost::filesystem::path path;

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::FILE);
		path = temp.getPath();
		CHECK(boost::filesystem::exists(path));
		CHECK(boost::filesystem::is_regular_file(path));
	}

	CHECK(!boost::filesystem::exists(path));
}

TEST_CASE("Test temporary directory functionality", "[fs]")
{
	boost::filesystem::path path;

	{
		tagit::fs::TemporaryStorage temp(
		        tagit::fs::TemporaryStorageType::DIRECTORY);
		path = temp.getPath();
		CHECK(boost::filesystem::exists(path));
		CHECK(boost::filesystem::is_directory(path));
	}

	CHECK(!boost::filesystem::exists(path));
}
