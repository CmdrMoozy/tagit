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

#ifndef TAGITCOMMON_FS_TEMPORARY_STORAGE_H
#define TAGITCOMMON_FS_TEMPORARY_STORAGE_H

#include <mutex>
#include <string>

namespace tagit
{
namespace fs
{
enum class TemporaryStorageType
{
	FILE,
	DIRECTORY
};

class TemporaryStorage
{
public:
	/*!
	 * Create a new temporary file or directory.
	 */
	TemporaryStorage(TemporaryStorageType type);

	TemporaryStorage(const TemporaryStorage &) = delete;

	/*!
	 * This destructor cleans up this object's temporary file or directory,
	 * ensuring that it no longer exists after destruction.
	 */
	~TemporaryStorage();

	TemporaryStorage &operator=(const TemporaryStorage &) = delete;

	/*!
	 * \return The path to this temporary file or directory.
	 */
	std::string getPath() const;

private:
	static std::mutex constructionMutex;

	TemporaryStorageType type;
	std::string path;
};
}
}

#endif
