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

#include "AudioFile.h"

#include <boost/variant.hpp>
#include <boost/optional/optional.hpp>

#include "tagitcommon/audio/WaveFile.h"

namespace
{
typedef boost::variant<tagit::audio::WaveFile> Variant_t;
}

namespace tagit
{
namespace audio
{
class AudioFile::Impl
{
public:
	Impl(const std::string &) : file()
	{
	}

private:
	Variant_t file;
};

AudioFile::AudioFile(const std::string &path) : impl(new Impl(path))
{
}

AudioFile::AudioFile(const AudioFile &other)
{
	*this = other;
}

AudioFile::~AudioFile()
{
}

AudioFile &AudioFile::operator=(const AudioFile &other)
{
	if(this == &other)
		return *this;

	impl.reset(new Impl(*other.impl));
	return *this;
}
}
}
