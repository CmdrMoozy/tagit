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

#include "FLACFile.h"

#include <cstring>
#include <stdexcept>

#include <taglib/id3v1tag.h>
#include <taglib/flacfile.h>
#include <taglib/xiphcomment.h>

#include "tagitcommon/audio/Utils.h"

namespace tagit
{
namespace audio
{
boost::optional<FLACFile>
FLACFile::factory(const io::MemoryMappedFile &memoryFile)
{
	// The file must be long enough to contain the FLAC magic number.
	if(memoryFile.getLength() < 4)
		return boost::none;

	// If the FLAC magic number isn't present, this isn't a FLAC file.
	if(memcmp(memoryFile.getData(), "fLaC", 4) != 0)
		return boost::none;

	return FLACFile();
}

FLACFile::FLACFile()
{
}

namespace visitor
{
std::shared_ptr<TagLib::File> tagLibFile(const std::string &path,
                                         const FLACFile &)
{
	return std::make_shared<TagLib::FLAC::File>(path.c_str(), true);
}

tagit::tag::Tag getTag(const FLACFile &, const TagLib::File *tagLibFile)
{
	const TagLib::FLAC::File *flacFile =
	        dynamic_cast<const TagLib::FLAC::File *>(tagLibFile);
	if(flacFile == nullptr)
		throw std::runtime_error("Wrong TagLib File type.");

	if(flacFile->hasXiphComment())
	{
		const TagLib::Ogg::XiphComment *tag =
		        const_cast<TagLib::FLAC::File *>(flacFile)
		                ->xiphComment();
		tagit::tag::Tag tagObj(tag);
		return tagObj;
	}
	else if(flacFile->hasID3v1Tag())
	{
		const TagLib::ID3v1::Tag *tag =
		        const_cast<TagLib::FLAC::File *>(flacFile)->ID3v1Tag();
		tagit::tag::Tag tagObj(tag);
		return tagObj;
	}
	else if(flacFile->hasID3v2Tag())
	{
		return utils::getID3v2Tag(
		        const_cast<TagLib::FLAC::File *>(flacFile)->ID3v2Tag());
	}

	return tagit::tag::Tag();
}
}
}
}
