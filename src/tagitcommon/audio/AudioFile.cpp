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

#include "tagitcommon/io/MemoryMappedFile.h"

namespace
{
#ifdef BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
static_assert(false, "boost::variant must support type sequences.");
#endif

struct CallFactoryFunction
{
	template <typename T>
	static tagit::audio::detail::OptVariant_t
	call(const tagit::io::MemoryMappedFile &memoryFile)
	{
		tagit::audio::detail::OptVariant_t variant = boost::none;
		boost::optional<T> opt = T::factory(memoryFile);
		if(!!opt)
			variant = std::move(*opt);
		return variant;
	}
};

template <typename Begin, typename End> struct FactoryForEachImpl
{
	static void factory(tagit::audio::detail::OptVariant_t &file,
	                    const tagit::io::MemoryMappedFile &memoryFile)
	{
		tagit::audio::detail::OptVariant_t ret =
		        CallFactoryFunction::template call<
		                typename Begin::type>(memoryFile);
		if(!!ret)
		{
			file = std::move(ret);
			return;
		}
		FactoryForEachImpl<typename boost::mpl::next<Begin>::type,
		                   End>::factory(file, memoryFile);
	}
};

template <typename End> struct FactoryForEachImpl<End, End>
{
	static void factory(tagit::audio::detail::OptVariant_t &,
	                    const tagit::io::MemoryMappedFile &)
	{
	}
};

template <typename Sequence>
void FactoryForEach(tagit::audio::detail::OptVariant_t &file,
                    const tagit::io::MemoryMappedFile &memoryFile)
{
	FactoryForEachImpl<
	        typename boost::mpl::begin<Sequence>::type,
	        typename boost::mpl::end<Sequence>::type>::factory(file,
	                                                           memoryFile);
}
}

namespace tagit
{
namespace audio
{
namespace detail
{
void audioFileFactory(OptVariant_t &file,
                      const io::MemoryMappedFile &memoryFile)
{
	FactoryForEach<Sequence_t>(file, memoryFile);
}
}

AudioFile::AudioFile(const std::string &path) : file(boost::none)
{
	io::MemoryMappedFile memoryFile(path);
	detail::audioFileFactory(file, memoryFile);
}

AudioFile::~AudioFile()
{
}
}
}
