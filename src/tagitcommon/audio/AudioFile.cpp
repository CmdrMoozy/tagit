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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>

namespace
{
#ifdef BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
static_assert(false, "boost::variant must support type sequences.");
#endif

struct CallFactoryFunction
{
	template <typename T>
	static tagit::audio::detail::OptVariant_t &&
	call(const std::string &path)
	{
		tagit::audio::detail::OptVariant_t variant = boost::none;
		boost::optional<T> opt = T::factory(path);
		if(!!opt)
			variant = std::move(*opt);
		return std::move(variant);
	}
};

template <typename Begin, typename End> struct FactoryForEachImpl
{
	static void factory(tagit::audio::detail::OptVariant_t &file,
	                    const std::string &path)
	{
		tagit::audio::detail::OptVariant_t ret =
		        CallFactoryFunction::template call<
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
	static void factory(tagit::audio::detail::OptVariant_t &,
	                    const std::string &)
	{
	}
};

template <typename Sequence>
void FactoryForEach(tagit::audio::detail::OptVariant_t &file,
                    const std::string &path)
{
	FactoryForEachImpl<
	        typename boost::mpl::begin<Sequence>::type,
	        typename boost::mpl::end<Sequence>::type>::factory(file, path);
}
}

namespace tagit
{
namespace audio
{
namespace detail
{
void audioFileFactory(OptVariant_t &file, const std::string &path)
{
	FactoryForEach<Sequence_t>(file, path);
}
}

AudioFile::AudioFile(const std::string &path) : file(boost::none)
{
	detail::audioFileFactory(file, path);
}

AudioFile::~AudioFile()
{
}
}
}
