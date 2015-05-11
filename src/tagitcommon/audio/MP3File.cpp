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

#include "MP3File.h"

#include <cstddef>
#include <cstring>

#include <taglib/mpegfile.h>

#include "tagitcommon/util/Bitwise.h"

namespace
{
/*!
 * This function returns the offset of the first MP3 frame in the given file.
 * This deals with skipping over the ID3v2 tag the file may contain, if any.
 *
 * \param file The memory mapped file to examine.
 * \return The offset of the first MP3 frame in the given file.
 */
std::size_t getFirstMP3FrameOffset(const tagit::io::MemoryMappedFile &file)
{
	const uint8_t *data = file.getData();
	if(file.getLength() < 10)
		return 0;

	if(memcmp(data, "ID3", 3) != 0)
		return 0;

	bool extended = data[5] & 0x4;
	bool footer = data[5] & 0x1;

	std::size_t headerSize = static_cast<std::size_t>(
	        tagit::bitwise::fromSynchsafe(data, 6));
	headerSize += 10; // Acount for the first part of the header.
	if(extended)
	{
		headerSize += static_cast<std::size_t>(
		        tagit::bitwise::fromSynchsafe(data, 10));
	}
	if(footer)
		headerSize += 10;

	return headerSize;
}

/*!
 * This function tests whether or not the given file is an MP3 file.
 *
 * \param file The memory mapped file to examine.
 * \return Whether or not the given file is an MP3 file.
 */
bool isMP3File(const tagit::io::MemoryMappedFile &file)
{
	std::size_t off = getFirstMP3FrameOffset(file);
	const uint8_t *data = file.getData();

	// If the file isn't long enough to contain the data before the first
	// MP3 frame as well as the first MP3 header, it isn't an MP3 file.
	if(file.getLength() < off + 4)
		return false;

	// The first MP3 frame header should start with 0xFFF (the MP3 sync
	// word). Next, it should contain the bits 101, where the first 1
	// indicates MPEG, and the following 01 indicates Layer 3.
	uint16_t sync = static_cast<uint16_t>(data[off]) << 8;
	sync |= data[off + 1] & 0xF0;
	uint8_t version = (data[off + 1] >> 3) & 0x1;
	uint8_t layer = (data[off + 1] >> 1) & 0x3;
	return (sync == 0xFFF0) && (version == 1) && (layer == 1);
}
}

namespace tagit
{
namespace audio
{
boost::optional<MP3File> MP3File::factory(const io::MemoryMappedFile &file)
{
	if(!isMP3File(file))
		return boost::none;

	return MP3File();
}

MP3File::MP3File()
{
}

namespace visitor
{
std::shared_ptr<TagLib::File> tagLibFile(const std::string &path,
                                         const MP3File &)
{
	return std::make_shared<TagLib::MPEG::File>(path.c_str(), true);
}
}
}
}
