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

#include "VorbisFile.h"

#include "tagitcommon/util/Bitwise.h"

#include <cstring>

namespace tagit
{
namespace audio
{
boost::optional<VorbisFile>
VorbisFile::factory(const io::MemoryMappedFile &memoryFile)
{
	// The file must be long enough to contain an Ogg/Vorbis header
	// with a single segment.
	if(memoryFile.getLength() < 28)
		return boost::none;

	// Ogg pages begin with a capture pattern "OggS".
	if(memcmp(memoryFile.getData(), "OggS", 4) != 0)
		return boost::none;

	// The Ogg page version should always be zero.
	if(memoryFile.getData()[4] != 0x00)
		return boost::none;

	// The first Ogg page should have the "Beginning of Stream" flag set.
	if(memoryFile.getData()[5] != 0x02)
		return boost::none;

	// The first Ogg page should have a page sequence number of 0.
	if(tagit::bitwise::integerFromBytes(memoryFile.getData(), 18) != 0)
		return boost::none;

	// This first page should contain one segment.
	if(memoryFile.getData()[26] != 0x01)
		return boost::none;

	// Get the length of the segment, and a pointer to the start of it.
	uint8_t length = memoryFile.getData()[27];
	if(memoryFile.getLength() < (28U + length))
		return boost::none;
	const uint8_t *segment = memoryFile.getData() + 28;

	// This segment must contain at least a packet type and "vorbis".
	if(length < 7)
		return boost::none;

	// This segment should be the identification header.
	if(segment[0] != 0x01)
		return boost::none;

	// The segment should then contain the word "vorbis".
	if(memcmp(segment + 1, "vorbis", 6) != 0)
		return boost::none;

	return VorbisFile();
}

VorbisFile::VorbisFile()
{
}
}
}
