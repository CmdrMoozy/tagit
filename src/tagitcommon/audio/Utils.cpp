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
#include <string>

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
}
}
}
