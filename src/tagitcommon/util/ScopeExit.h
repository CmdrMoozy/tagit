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

#ifndef TAGITCOMMON_UTIL_SCOPE_EXIT_H
#define TAGITCOMMON_UTIL_SCOPE_EXIT_H

#include <functional>

namespace tagit
{
namespace util
{
class ScopeExit
{
public:
	/*!
	 * \param f The function to execute on destruction.
	 */
	ScopeExit(const std::function<void()> &f);

	/*!
	 * This destructor executes the function specified in the constructor.
	 * (Generally, this executes the given function when this object
	 * leaves the scope it was constructed in.)
	 */
	~ScopeExit();

private:
	std::function<void()> function;
};
}
}

#endif
