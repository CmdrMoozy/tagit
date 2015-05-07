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

#ifndef TAGITCOMMON_UTIL_BITWISE_H
#define TAGITCOMMON_UTIL_BITWISE_H

#include <cstddef>
#include <cstdint>

namespace tagit
{
namespace bitwise
{
/*!
 * This function converts a "32-bit synchsafe integer" found e.g. in MP3
 * headers, and converts it to a standard 32-bit integer type.
 *
 * These "synchsafe integers" are more or less 32-bit integers, except every
 * 8th bit is ignored. So:
 *
 *     1111 1111 1111 1111 (0xFFFF) =>  0011 0111 1111 0111 1111 (0x37F7F)
 *
 * \param data The buffer containing the integer.
 * \param off The offset in the buffer at which the integer starts.
 * \return The value as a normal 32-bit integer.
 */
uint32_t fromSynchsafe(const uint8_t *data, std::size_t off = 0);

/*!
 * This function writes the given 32-bit integer to the given buffer at the
 * given offset as a "32-bit synchsafe integer". For more information on what
 * exactly this format means, see fromSynchsafe().
 *
 * \param data THe buffer to write the integer to.
 * \param off The offset in the buffer to write the integer at.
 * \param v The value to write.
 */
void toSynchsafe(uint32_t *data, std::size_t off, uint32_t v);
}
}

#endif
