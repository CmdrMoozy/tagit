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

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>

#include <QFileInfo>

#include "tagitcommon/io/MemoryMappedFile.h"

namespace
{
#ifdef BOOST_VARIANT_NO_TYPE_SEQUENCE_SUPPORT
static_assert(false, "boost::variant must support type sequences.");
#endif

template <typename A, typename B> int compareUInts(A a, B b)
{
	if(a < b)
		return -1;
	else if(a > b)
		return 1;
	else
		return 0;
}

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

TagLibFileVisitor::TagLibFileVisitor(const std::string &p) : path(p)
{
}

GetTagVisitor::GetTagVisitor(const TagLib::File *f) : tagLibFile(f)
{
}
}

AudioFile::AudioFile() : path(), file(boost::none), tagLibFile(nullptr)
{
}

AudioFile::AudioFile(const std::string &p)
        : path(), file(boost::none), tagLibFile(nullptr)
{
	boost::filesystem::path pathObj(p);
	if(!boost::filesystem::exists(pathObj))
		return;
	pathObj = boost::filesystem::absolute(
	        boost::filesystem::canonical(pathObj));
	path = pathObj.string();

	io::MemoryMappedFile memoryFile(path);
	detail::audioFileFactory(file, memoryFile);
	if(!file)
		path.clear();

	if(!!file)
	{
		detail::TagLibFileVisitor fileVisitor(path);
		tagLibFile = boost::apply_visitor(fileVisitor, *file);

		detail::GetTagVisitor tagVisitor(tagLibFile.get());
		tag = boost::apply_visitor(tagVisitor, *file);
	}
}

bool AudioFile::operator!() const
{
	return !file;
}

std::string AudioFile::getPath() const
{
	return path;
}

std::string AudioFile::getFilename() const
{
	boost::filesystem::path pathObj(path);
	return pathObj.filename().string();
}

const tagit::tag::Tag &AudioFile::getTag() const
{
	return tag;
}

bool AudioFileComparator::operator()(const AudioFile &a, const AudioFile &b)
{
	if(!!a && !!b)
	{
		int cmp = a.getTag().artist.compare(b.getTag().artist);
		if(cmp != 0)
			return cmp < 0;

		cmp = compareUInts(a.getTag().year, b.getTag().year);
		if(cmp != 0)
			return cmp < 0;

		cmp = a.getTag().album.compare(b.getTag().album);
		if(cmp != 0)
			return cmp < 0;

		cmp = compareUInts(a.getTag().cd, b.getTag().cd);
		if(cmp != 0)
			return cmp < 0;

		cmp = compareUInts(a.getTag().track, b.getTag().track);
		if(cmp != 0)
			return cmp < 0;

		cmp = a.getTag().title.compare(b.getTag().title);
		if(cmp != 0)
			return cmp < 0;
	}

	if(!a && !!b)
		return false;
	else if(!!a && !b)
		return true;

	return a.getFilename().compare(b.getFilename()) < 0;
}
}
}
