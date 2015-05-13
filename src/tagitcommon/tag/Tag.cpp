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

#include "Tag.h"

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <vector>

#include <taglib/tag.h>
#include <taglib/tstring.h>

namespace tagit
{
namespace tag
{
namespace util
{
const char *getTagGenre(uint8_t id)
{
	for(auto it = TAG_GENRE_MAP_BEGIN; it != TAG_GENRE_MAP_END; ++it)
	{
		if(it->first == id)
			return it->second.get();
	}

	throw std::runtime_error("Tag genre not found.");
}

uint8_t getTagGenreID(const std::string &tag)
{
	for(auto it = TAG_GENRE_MAP_BEGIN; it != TAG_GENRE_MAP_END; ++it)
	{
		if(strcmp(it->second.get(), tag.c_str()) == 0)
			return it->first;
	}

	throw std::runtime_error("Tag genre ID not found.");
}

QString tagStringToQString(const TagLib::String &str)
{
	static_assert(sizeof(wchar_t) >= 2,
	              "wchar_t must be at least two bytes wide.");
	static_assert(sizeof(ushort) >= 2,
	              "ushort must be at least two bytes wide.");

	std::vector<ushort> copy(str.length() + 1);
	copy[0] = 0xFEFF;
	std::copy(str.begin(), str.end(), copy.data() + 1);

	return QString::fromUtf16(copy.data(), copy.size());
}

TagLib::String qstringToTagString(const QString &str)
{
	static_assert(sizeof(wchar_t) >= 2,
	              "wchar_t must be at least two bytes wide.");
	static_assert(sizeof(ushort) >= 2,
	              "ushort must be at least two bytes wide.");

	std::vector<wchar_t> copy(
	        static_cast<std::vector<wchar_t>::size_type>(str.length()) + 1);
	copy[copy.size() - 1] = 0;
	const ushort *data = str.utf16();
	std::copy(data, data + str.length(), copy.data());

	return TagLib::String(copy.data());
}
}

Tag::Tag()
        : title(""),
          artist(""),
          album(""),
          cd(0),
          year(0),
          track(0),
          tracks(0),
          genre("")
{
}

Tag::Tag(const TagLib::Tag *tag) : Tag()
{
	title = util::tagStringToQString(tag->title());
	artist = util::tagStringToQString(tag->artist());
	album = util::tagStringToQString(tag->album());
	year = static_cast<uint64_t>(tag->year());
	track = static_cast<uint64_t>(tag->track());
	genre = util::tagStringToQString(tag->genre());
}
}
}
