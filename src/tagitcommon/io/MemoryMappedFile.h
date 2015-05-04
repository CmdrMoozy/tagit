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

#ifndef TAGITCOMMON_IO_MEMORY_MAPPED_FILE_H
#define TAGITCOMMON_IO_MEMORY_MAPPED_FILE_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace tagit
{
namespace io
{
class MemoryMappedFile
{
public:
	/*!
	 * \param path The file to map into memory.
	 */
	MemoryMappedFile(const std::string &path);

	MemoryMappedFile(const MemoryMappedFile &) = delete;

	/*!
	 * Closes the previously mapped file, freeing system resources.
	 */
	~MemoryMappedFile();

	MemoryMappedFile &operator=(const MemoryMappedFile &) = delete;

	/*!
	 * \return A pointer to the beginning of the file's contents.
	 */
	const uint8_t *getData() const;

	/*!
	 * \return The size of the file, in bytes.
	 */
	std::size_t getLength() const;

private:
	int fileDescriptor;
	uint8_t *file;
	std::size_t length;
};
}
}

#endif
