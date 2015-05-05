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

#ifndef TAGITCOMMON_UTIL_VARIANT_UTILS_H
#define TAGITCOMMON_UTIL_VARIANT_UTILS_H

#include <boost/variant.hpp>

namespace tagit
{
namespace variant_util
{
namespace detail
{
template <typename CheckT>
struct VariantIsVisitor : public boost::static_visitor<bool>
{
	template <typename T> bool operator()(const T &)
	{
		return false;
	}

	bool operator()(const CheckT &)
	{
		return true;
	}
};
}

template <typename T, typename... VariantType>
bool variantIs(const boost::variant<VariantType...> &variant)
{
	detail::VariantIsVisitor<T> visitor;
	return boost::apply_visitor(visitor, variant);
}
}
}

#endif
