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

#include "Bitwise.h"

namespace tagit
{
namespace bitwise
{
uint32_t fromSynchsafe(const uint8_t *data, std::size_t off)
{
	uint32_t result = 0;
	result |= static_cast<uint32_t>(data[off + 0] & 0x7F) << 21;
	result |= static_cast<uint32_t>(data[off + 1] & 0x7F) << 14;
	result |= static_cast<uint32_t>(data[off + 2] & 0x7F) << 7;
	result |= static_cast<uint32_t>(data[off + 3] & 0x7F);
	return result;
}

void toSynchsafe(uint32_t *data, std::size_t off, uint32_t v)
{
	data[off + 3] = static_cast<uint8_t>(v & 0x7F);
	data[off + 2] = static_cast<uint8_t>((v >> 7) & 0x7F);
	data[off + 1] = static_cast<uint8_t>((v >> 14) & 0x7F);
	data[off + 0] = static_cast<uint8_t>((v >> 21) & 0x7F);
}
}
}
