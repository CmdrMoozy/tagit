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

#ifndef TAGITCOMMON_FS_ENVIRONMENT_H
#define TAGITCOMMON_FS_ENVIRONMENT_H

#include <string>
#include <vector>
#include <experimental/optional>

namespace tagit
{
namespace fs
{
/*!
 * This function returns the contents of the operating system's executable
 * path, split up into separate strings.
 *
 * \return The executable path components.
 */
std::vector<std::string> getSystemPath();

/*!
 * This function is analogous to the standard UNIX `which` command, which
 * returns the path to a given executable in the environment's PATH.
 *
 * \param command The command to search for.
 * \return The path to the given command, or nullopt if not found.
 */
std::experimental::optional<std::string> which(const std::string &command);
}
}

#endif
