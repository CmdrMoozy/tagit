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

#include "WaveFile.h"

#include <cstring>

#include <taglib/wavfile.h>

namespace tagit
{
namespace audio
{
boost::optional<WaveFile>
WaveFile::factory(const io::MemoryMappedFile &memoryFile)
{
	// The file should start with a RIFF header and a length. After that,
	// a "WAVE" chunk should be present.

	if(memoryFile.getLength() < 12)
		return boost::none;

	if(std::memcmp(memoryFile.getData(), "RIFF", 4) != 0)
		return boost::none;

	if(std::memcmp(memoryFile.getData() + 8, "WAVE", 4) != 0)
		return boost::none;

	return WaveFile();
}

WaveFile::WaveFile()
{
}

namespace visitor
{
std::shared_ptr<TagLib::File> tagLibFile(const std::string &path,
                                         const WaveFile &)
{
	return std::make_shared<TagLib::RIFF::WAV::File>(path.c_str(), true);
}
}
}
}
