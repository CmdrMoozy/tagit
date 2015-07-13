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

#ifndef TAGITCOMMON_AUDIO_FLAC_FILE_H
#define TAGITCOMMON_AUDIO_FLAC_FILE_H

#include <memory>
#include <string>
#include <experimental/optional>

#include <taglib/fileref.h>

#include "tagitcommon/io/MemoryMappedFile.h"
#include "tagitcommon/tag/Tag.h"

namespace tagit
{
namespace audio
{
/*!
 * \brief This class provides FLAC functionality.
 */
class FLACFile
{
public:
	/*!
	 * Try to construct a new FLACFile object from the given raw data
	 * file. If the given file is not a valid FLAC file, then nullopt
	 * is returned instead.
	 *
	 * \param memoryFile The file to construct an FLACFile from.
	 * \return The resulting FLACFile.
	 */
	static std::experimental::optional<FLACFile>
	factory(const io::MemoryMappedFile &memoryFile);

private:
	FLACFile();
};

namespace visitor
{
std::shared_ptr<TagLib::File> tagLibFile(const std::string &path,
                                         const FLACFile &file);

tagit::tag::Tag getTag(const FLACFile &file, const TagLib::File *tagLibFile);
}
}
}

#endif
