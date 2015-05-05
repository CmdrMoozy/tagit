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

#ifndef TAGITCOMMON_AUDIO_AUDIO_FILE_H
#define TAGITCOMMON_AUDIO_AUDIO_FILE_H

#include <memory>
#include <string>

#include <boost/variant.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/optional/optional.hpp>

#include "tagitcommon/audio/WaveFile.h"

namespace tagit
{
namespace audio
{
namespace detail
{
typedef boost::mpl::vector<tagit::audio::WaveFile> Sequence_t;
typedef boost::make_variant_over<Sequence_t>::type Variant_t;
typedef boost::optional<Variant_t> OptVariant_t;

void audioFileFactory(OptVariant_t &file, const std::string &path);

class AudioFileImpl
{
public:
	AudioFileImpl(const std::string &path);

private:
	OptVariant_t file;
};
}

class AudioFile
{
public:
	AudioFile(const std::string &path);

	AudioFile(const AudioFile &other);

	~AudioFile();

	AudioFile &operator=(const AudioFile &other);

private:
	std::unique_ptr<detail::AudioFileImpl> impl;
};
}
}

#endif
