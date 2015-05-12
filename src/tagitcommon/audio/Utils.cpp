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

#include "Utils.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <locale>
#include <stdexcept>
#include <string>

#include <taglib/mp4item.h>
#include <taglib/mp4tag.h>

#include "tagitcommon/util/Bitwise.h"

namespace tagit
{
namespace audio
{
namespace utils
{
bool isMP4AudioFile(const tagit::io::MemoryMappedFile &file)
{
	// The file must be long enough to store at least one atom length.
	if(file.getLength() < 4)
		return false;

	// The file must be long enough for this atom.
	uint32_t length = tagit::bitwise::integerFromBytes(file.getData());
	if(file.getLength() < length)
		return false;

	// The first atom should be an "ftyp" atom.
	if(memcmp(file.getData() + 4, "ftyp", 4) != 0)
		return false;

	// Search for an "M4A " ftyp, indicating that this is an audio file.
	bool found = false;
	std::locale locale;
	auto toLowerOp = [&locale](const char &c) -> char
	{
		return std::tolower(c, locale);
	};
	for(const uint8_t *ftyp = file.getData() + 8;
	    ftyp < file.getData() + length; ftyp += 4)
	{
		std::string s(reinterpret_cast<const char *>(ftyp), 4);
		std::transform(s.cbegin(), s.cend(), s.begin(), toLowerOp);
		if(s == "m4a ")
		{
			found = true;
			break;
		}
	}

	return found;
}

tagit::tag::Tag getMP4Tag(const TagLib::File *tagLibFile)
{
	const TagLib::MP4::Tag *tag =
	        dynamic_cast<const TagLib::MP4::Tag *>(tagLibFile->tag());
	if(tag == nullptr)
		throw std::runtime_error("Invalid TagLib file type.");
	const TagLib::MP4::ItemListMap &itemMap =
	        const_cast<TagLib::MP4::Tag *>(tag)->itemListMap();

	tagit::tag::Tag tagObj(tag);
	auto it = itemMap.find("disk");
	if(it != itemMap.end())
		tagObj.cd = static_cast<uint64_t>(it->second.toUInt());

	return tagObj;
}

tagit::tag::Tag getID3v2Tag(const TagLib::ID3v2::Tag *tag)
{
	tagit::tag::Tag tagObj(tag);

	auto cdIt = tag->frameListMap().find("TPOS");
	if(cdIt != tag->frameListMap().end())
	{
		TagLib::String cd = cdIt->second.front()->toString();
		int slashOff = cd.find("/");
		if(slashOff != -1)
		{
			cd = cd.substr(static_cast<TagLib::uint>(slashOff + 1));
			tagObj.cd =
			        static_cast<uint64_t>(std::stoul(cd.to8Bit()));
		}
	}

	auto tracksIt = tag->frameListMap().find("TRCK");
	if(tracksIt != tag->frameListMap().end())
	{
		TagLib::String tracks = tracksIt->second.front()->toString();
		int slashOff = tracks.find("/");
		if(slashOff != -1)
		{
			tracks = tracks.substr(
			        static_cast<TagLib::uint>(slashOff + 1));
			tagObj.tracks = static_cast<uint64_t>(
			        std::stoul(tracks.to8Bit()));
		}
	}

	return tagObj;
}
}
}
}
