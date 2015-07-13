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

#include "ALACFile.h"

#include <taglib/mp4file.h>

#include "tagitcommon/audio/Utils.h"
#include "tagitcommon/tag/TaggedFile.h"

namespace tagit
{
namespace audio
{
std::experimental::optional<ALACFile>
ALACFile::factory(const io::MemoryMappedFile &memoryFile)
{
	// If the given file isn't an MP4 file, it can't be an ALAC file.
	if(!utils::isMP4AudioFile(memoryFile))
		return std::experimental::nullopt;

	// Use TagLib to differentiate AAC versus ALAC.
	tagit::tag::TaggedFile<TagLib::MP4::File> tag(memoryFile);
	if(tag.get().audioProperties()->codec() !=
	   TagLib::MP4::Properties::ALAC)
	{
		return std::experimental::nullopt;
	}

	return ALACFile();
}

ALACFile::ALACFile()
{
}

namespace visitor
{
std::shared_ptr<TagLib::File> tagLibFile(const std::string &path,
                                         const ALACFile &)
{
	return std::make_shared<TagLib::MP4::File>(path.c_str(), true);
}

tagit::tag::Tag getTag(const ALACFile &, const TagLib::File *tagLibFile)
{
	return utils::getMP4Tag(tagLibFile);
}
}
}
}
