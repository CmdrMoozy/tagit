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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#include <QString>

#include <taglib/fileref.h>
#include <taglib/tstring.h>

#include "tagitcommon/util/ConstexprString.h"

namespace tagit
{
namespace tag
{
namespace util
{
constexpr std::pair<uint8_t, tagit::util::ConstexprString> TAG_GENRE_MAP[] = {
        {0x00, "Blues"},
        {0x01, "Classic Rock"},
        {0x02, "Country"},
        {0x03, "Dance"},
        {0x04, "Disco"},
        {0x05, "Funk"},
        {0x06, "Grunge"},
        {0x07, "Hip-Hop"},
        {0x08, "Jazz"},
        {0x09, "Metal"},
        {0x0A, "New Age"},
        {0x0B, "Oldies"},
        {0x0C, "Other"},
        {0x0D, "Pop"},
        {0x0E, "Rhythm and Blues"},
        {0x0F, "Rap"},
        {0x10, "Reggae"},
        {0x11, "Rock"},
        {0x12, "Techno"},
        {0x13, "Industrial"},
        {0x14, "Alternative"},
        {0x15, "Ska"},
        {0x16, "Death Metal"},
        {0x17, "Pranks"},
        {0x18, "Soundtrack"},
        {0x19, "Euro-Techno"},
        {0x1A, "Ambient"},
        {0x1B, "Trip-Hop"},
        {0x1C, "Vocal"},
        {0x1D, "Jazz & Funk"},
        {0x1E, "Fusion"},
        {0x1F, "Trance"},
        {0x20, "Classical"},
        {0x21, "Instrumental"},
        {0x22, "Acid"},
        {0x23, "House"},
        {0x24, "Game"},
        {0x25, "Sound Clip"},
        {0x26, "Gospel"},
        {0x27, "Noise"},
        {0x28, "Alternative Rock"},
        {0x29, "Bass"},
        {0x2A, "Soul"},
        {0x2B, "Punk rock"},
        {0x2C, "Space"},
        {0x2D, "Meditative"},
        {0x2E, "Instrumental Pop"},
        {0x2F, "Instrumental Rock"},
        {0x30, "Ethnic"},
        {0x31, "Gothic"},
        {0x32, "Darkwave"},
        {0x33, "Techno-Industrial"},
        {0x34, "Electronic"},
        {0x35, "Pop-Folk"},
        {0x36, "Eurodance"},
        {0x37, "Dream"},
        {0x38, "Southern Rock"},
        {0x39, "Comedy"},
        {0x3A, "Cult"},
        {0x3B, "Gangsta"},
        {0x3C, "Top 40"},
        {0x3D, "Christian Rap"},
        {0x3E, "Pop/Funk"},
        {0x3F, "Jungle"},
        {0x40, "Native American"},
        {0x41, "Cabaret"},
        {0x42, "New Wave"},
        {0x43, "Psychedelic"},
        {0x44, "Rave"},
        {0x45, "Showtunes"},
        {0x46, "Trailer"},
        {0x47, "Lo-Fi"},
        {0x48, "Tribal"},
        {0x49, "Acid Punk"},
        {0x4A, "Acid Jazz"},
        {0x4B, "Polka"},
        {0x4C, "Retro"},
        {0x4D, "Musical"},
        {0x4E, "Rock & Roll"},
        {0x4F, "Hard Rock"}};

constexpr std::size_t TAG_GENRE_MAP_SIZE =
        sizeof(TAG_GENRE_MAP) / sizeof(TAG_GENRE_MAP[0]);

constexpr std::remove_reference<decltype(TAG_GENRE_MAP[0])>::type *
        TAG_GENRE_MAP_BEGIN = &TAG_GENRE_MAP[0];
constexpr std::remove_reference<decltype(TAG_GENRE_MAP[0])>::type *
        TAG_GENRE_MAP_END = &TAG_GENRE_MAP[TAG_GENRE_MAP_SIZE];

const char *getTagGenre(uint8_t id);
uint8_t getTagGenreID(const std::string &tag);

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
