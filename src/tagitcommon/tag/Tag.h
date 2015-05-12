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

#ifndef TAGITCOMMON_TAG_TAG_H
#define TAGITCOMMON_TAG_TAG_H

#include <cstdint>

#include <QString>

#include <taglib/fileref.h>
#include <taglib/tstring.h>

namespace tagit
{
namespace tag
{
namespace util
{
QString tagStringToQString(const TagLib::String &str);
}

struct Tag
{
	QString title;
	QString artist;
	QString album;
	uint64_t cd;
	uint64_t year;
	uint64_t track;
	uint64_t tracks;
	QString genre;

	Tag();

	/*!
	 * Load most portions of a Tag structure from the given generic TagLib
	 * tag. Note that this doesn't include all fields: "cd" and "tracks"
	 * are nonstandard, and are not supported by all tag types.
	 *
	 * \param tag The TagLib tag structure to load data from.
	 */
	Tag(const TagLib::Tag *tag);

	Tag(const Tag &) = default;
	~Tag() = default;

	Tag &operator=(const Tag &) = default;
};
}
}

#endif
