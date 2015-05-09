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

#include "BitwiseTest.h"

#include "tagitcommon/util/Bitwise.h"

namespace
{
void testSwitchEndianness(uint32_t exp, uint32_t v)
{
	vrfy::assert::assertEquals(exp, tagit::bitwise::switchEndianness(v));
}

void testSwitchEndianness()
{
	testSwitchEndianness(0x0A0B0C0D, 0x0D0C0B0A);
	testSwitchEndianness(0x0D0C0B0A, 0x0A0B0C0D);
}
}

namespace tagit_test
{
namespace util
{
void BitwiseTest::test()
{
	testSwitchEndianness();
}
}
}
