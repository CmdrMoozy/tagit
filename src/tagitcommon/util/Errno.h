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

#ifndef TAGITCOMMON_UTIL_ERRNO_H
#define TAGITCOMMON_UTIL_ERRNO_H

#include <string>

#include <boost/optional/optional.hpp>

namespace tagit
{
namespace util
{
/*!
 * This function returns a human readable string for the given error number.
 *
 * \param error The error number to interpret. Defaults to errno.
 * \param defaultMessage The default error message to return.
 * \return A human readable error message for the given error.
 */
std::string getErrnoError(boost::optional<int> error = boost::none,
                          const std::string &defaultMessage = "Unknown error.");

/*!
 * Throw an exception with the getErrnoError() message for the given error.
 *
 * \param error The error number to interpret. Defaults to errno.
 * \param defaultMessage The default error message to return.
 */
void throwErrnoError(boost::optional<int> error = boost::none,
                     const std::string &defaultMessage = "Unknown error.");
}
}

#endif
