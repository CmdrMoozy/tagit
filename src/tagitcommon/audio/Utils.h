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

#ifndef TAGITCOMMON_AUDIO_UTILS_H
#define TAGITCOMMON_AUDIO_UTILS_H

#include <taglib/id3v2tag.h>

#include "tagitcommon/io/MemoryMappedFile.h"
#include "tagitcommon/tag/Tag.h"

namespace tagit
{
namespace audio
{
namespace utils
{
/*!
 * \param file The file to examine.
 * \return True if the file is an MP4 audio file (AAC or ALAC).
 */
bool isMP4AudioFile(const tagit::io::MemoryMappedFile &file);

tagit::tag::Tag getMP4Tag(const TagLib::File *tagLibFile);

tagit::tag::Tag getID3v2Tag(const TagLib::ID3v2::Tag *tag);
}
}
}

#endif
