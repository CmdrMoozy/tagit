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

#ifndef TAGITCOMMON_TAG_TAGGED_FILE_H
#define TAGITCOMMON_TAG_TAGGED_FILE_H

#include <taglib/audioproperties.h>
#include <taglib/tbytevector.h>
#include <taglib/tbytevectorstream.h>

#include "tagitcommon/io/MemoryMappedFile.h"

namespace tagit
{
namespace tag
{
template <typename T> class TaggedFile
{
public:
	TaggedFile(const tagit::io::MemoryMappedFile &memoryFile,
	           bool readProperties = true,
	           TagLib::AudioProperties::ReadStyle audioPropertiesStyle =
	                   TagLib::AudioProperties::Average)
	        : byteVector(
	                  reinterpret_cast<const char *>(memoryFile.getData()),
	                  memoryFile.getLength()),
	          byteVectorStream(byteVector),
	          file(&byteVectorStream, readProperties, audioPropertiesStyle)
	{
	}

	T &get()
	{
		return file;
	}

private:
	TagLib::ByteVector byteVector;
	TagLib::ByteVectorStream byteVectorStream;
	T file;
};
}
}

#endif
