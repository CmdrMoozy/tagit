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

#ifndef TAGITCOMMON_AUDIO_MP3_FILE_H
#define TAGITCOMMON_AUDIO_MP3_FILE_H

#include <boost/optional/optional.hpp>

#include "tagitcommon/io/MemoryMappedFile.h"

namespace tagit
{
namespace audio
{
/*!
 * \brief This class provides MP3-related functionality.
 */
class MP3File
{
public:
	/*!
	 * Try to construct a new MP3File object from the given raw data
	 * file. If the given file is not a valid MP3 file, then boost::none
	 * is returned instead.
	 *
	 * \param memoryFile The file to construct an MP3File from.
	 * \return The resulting MP3File.
	 */
	static boost::optional<MP3File>
	factory(const io::MemoryMappedFile &memoryFile);

private:
	MP3File();
};
}
}

#endif
