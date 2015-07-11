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

#ifndef TAGITCOMMON_UTIL_CONSTEXPR_STRING_H
#define TAGITCOMMON_UTIL_CONSTEXPR_STRING_H

#include <cstddef>
#include <stdexcept>

namespace tagit
{
namespace util
{
class ConstexprString
{
public:
	template <std::size_t N>
	constexpr ConstexprString(const char(&s)[N])
	        : string(s), sz(N - 1)
	{
		static_assert(N >= 1,
		              "Can't construct from invalid string literal.");
	}

	constexpr std::size_t size() const
	{
		return sz;
	}

	constexpr char operator[](std::size_t idx) const
	{
		return idx < sz ? string[idx]
		                : throw std::out_of_range(
		                          "Invalid string index.");
	}

	constexpr bool operator==(const ConstexprString &o) const
	{
		return equals(o, 0);
	}

	const char *get() const
	{
		return string;
	}

private:
	const char *string;
	std::size_t sz;

	constexpr bool equals(const ConstexprString &o, std::size_t idx) const
	{
		return sz != o.size()
		               ? false
		               : idx >= sz ? true : operator[](idx) == o[idx] &&
		                                            equals(o, idx + 1);
	}
};
}
}

#endif
