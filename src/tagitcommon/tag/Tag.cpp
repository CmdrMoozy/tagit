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

#include <taglib/tag.h>
#include <taglib/tstring.h>

namespace tagit
{
namespace tag
{
namespace util
{
QString tagStringToQString(const TagLib::String &str)
{
	return QString::fromUtf16(
	        reinterpret_cast<const ushort *>(str.toCWString()),
	        static_cast<int>(str.length()));
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
