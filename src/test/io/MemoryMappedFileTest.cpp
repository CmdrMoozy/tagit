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

#include <cstring>
#include <fstream>
#include <sstream>

#include "tagitcommon/fs/TemporaryStorage.h"
#include "tagitcommon/io/MemoryMappedFile.h"

TEST_CASE("Test memory mapped I/O functionality", "[io]")
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

		tagit::io::MemoryMappedFile file(temp.getPath());
		CHECK(expected == file.getLength());
		CHECK(0 == std::memcmp(contents.c_str(), file.getData(),
		                       file.getLength()));
	}
}
