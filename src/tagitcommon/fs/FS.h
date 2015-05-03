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

#ifndef TAGITCOMMON_FS_FS_H
#define TAGITCOMMON_FS_FS_H

#include <string>

namespace tagit
{
namespace fs
{
/*!
 * This function returns the path the given symlink points to, or the given
 * path unchanged if it isn' a symlink.
 *
 * \param path The path to de-symlink.
 * \return The dereferenced path.
 */
std::string stripSymlink(const std::string &path);

/*!
 * This function will create a new, empty file at the given path. If the given
 * path already exists, or some error occurs, then an exception will be
 * thrown.
 *
 * \param path The path of the file to create.
 */
void createFile(const std::string &path);

/*!
 * \param target The target path the symlink will link to.
 * \param link The path to the newly created symlink.
 */
void createSymlink(const std::string &target, const std::string &link);

/*!
 * \param path The path to inspect.
 * \return Whether or not the given path is a file.
 */
bool isFile(const std::string &path);

/*!
 * \param path Te path to inspect.
 * \return Whether or not the given path is executable.
 */
bool isExecutable(const std::string &path);
}
}

#endif
