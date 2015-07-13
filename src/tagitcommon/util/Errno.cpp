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

#include "Errno.h"

#include <cerrno>
#include <cstring>
#include <stdexcept>

namespace tagit
{
namespace util
{
std::string getErrnoError(std::experimental::optional<int> error,
                          const std::string &defaultMessage)
{
	if(!error)
		error = errno;

	std::string errorString = defaultMessage;

	char buf[1024];
	return std::string(strerror_r(*error, buf, 1024));
}

void throwErrnoError(std::experimental::optional<int> error,
                     const std::string &defaultMessage)
{
	throw std::runtime_error(getErrnoError(error, defaultMessage));
}
}
}
