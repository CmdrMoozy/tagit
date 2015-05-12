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

#include <taglib/fileref.h>

#include "tagitcommon/audio/AACFile.h"
#include "tagitcommon/audio/ALACFile.h"
#include "tagitcommon/audio/FLACFile.h"
#include "tagitcommon/audio/MP3File.h"
#include "tagitcommon/audio/VorbisFile.h"
#include "tagitcommon/audio/WaveFile.h"
#include "tagitcommon/tag/Tag.h"
#include "tagitcommon/util/VariantUtils.h"

namespace tagit
{
namespace audio
{
namespace detail
{
typedef boost::mpl::vector<tagit::audio::AACFile, tagit::audio::ALACFile,
                           tagit::audio::FLACFile, tagit::audio::MP3File,
                           tagit::audio::VorbisFile,
                           tagit::audio::WaveFile> Sequence_t;
typedef boost::make_variant_over<Sequence_t>::type Variant_t;
typedef boost::optional<Variant_t> OptVariant_t;

void audioFileFactory(OptVariant_t &file, const std::string &path);

struct TagLibFileVisitor
        : public boost::static_visitor<std::shared_ptr<TagLib::File>>
{
	const std::string path;

	TagLibFileVisitor(const std::string &p);

	TagLibFileVisitor(const TagLibFileVisitor &) = default;
	~TagLibFileVisitor() = default;

	TagLibFileVisitor &operator=(const TagLibFileVisitor &) = default;

	template <typename T>
	std::shared_ptr<TagLib::File> operator()(const T &t)
	{
		return tagit::audio::visitor::tagLibFile(path, t);
	}
};

struct GetTagVisitor : public boost::static_visitor<tagit::tag::Tag>
{
	const TagLib::File *tagLibFile;

	GetTagVisitor(const TagLib::File *f);

	GetTagVisitor(const GetTagVisitor &) = default;
	~GetTagVisitor() = default;

	GetTagVisitor &operator=(const GetTagVisitor &) = default;

	template <typename T> tagit::tag::Tag operator()(const T &t)
	{
		return tagit::audio::visitor::getTag(t, tagLibFile);
	}
};
}

class AudioFile
{
public:
	AudioFile();
	AudioFile(const std::string &p);

	AudioFile(const AudioFile &) = delete;
	AudioFile(AudioFile &&) = default;

	~AudioFile() = default;

	AudioFile &operator=(const AudioFile &) = delete;
	AudioFile &operator=(AudioFile &&) = default;

	bool operator!() const;

	template <typename T> bool is()
	{
		if(!file)
			return false;
		return variant_util::variantIs<T>(*file);
	}

	std::string getPath() const;
	std::string getFilename() const;

	const tagit::tag::Tag &getTag() const;

private:
	std::string path;
	detail::OptVariant_t file;
	std::shared_ptr<TagLib::File> tagLibFile;
	tagit::tag::Tag tag;
};

struct AudioFileComparator
{
	bool operator()(const AudioFile &a, const AudioFile &b);
};
}
}

#endif
