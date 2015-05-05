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

#include <utility>

#include <boost/variant.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/optional/optional.hpp>

#include "tagitcommon/audio/WaveFile.h"

namespace
{
#ifdef BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
static_assert(false, "boost::variant must support type sequences.");
#endif

typedef boost::mpl::vector<tagit::audio::WaveFile> Sequence_t;
typedef boost::make_variant_over<Sequence_t>::type Variant_t;
typedef boost::optional<Variant_t> OptVariant_t;

struct CallFactoryFunction
{
	template <typename T>
	static OptVariant_t &&call(const std::string &path)
	{
		OptVariant_t variant = boost::none;
		boost::optional<T> opt = T::factory(path);
		if(!!opt)
			variant = std::move(*opt);
		return std::move(variant);
	}
};

template <typename Begin, typename End> struct FactoryForEachImpl
{
	static void factory(OptVariant_t &file, const std::string &path)
	{
		OptVariant_t ret = CallFactoryFunction::template call<
		        typename Begin::type>(path);
		if(!!ret)
		{
			file = std::move(ret);
			return;
		}
		FactoryForEachImpl<typename boost::mpl::next<Begin>::type,
		                   End>::factory(file, path);
	}
};

template <typename End> struct FactoryForEachImpl<End, End>
{
	static void factory(OptVariant_t &, const std::string &)
	{
	}
};

template <typename Sequence>
void FactoryForEach(OptVariant_t &file, const std::string &path)
{
	FactoryForEachImpl<
	        typename boost::mpl::begin<Sequence>::type,
	        typename boost::mpl::end<Sequence>::type>::factory(file, path);
}

void audioFileFactory(OptVariant_t &file, const std::string &path)
{
	FactoryForEach<Sequence_t>(file, path);
}
}

namespace tagit
{
namespace audio
{
class AudioFile::Impl
{
public:
	Impl(const std::string &path) : file(boost::none)
	{
		audioFileFactory(file, path);
	}

private:
	OptVariant_t file;
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
