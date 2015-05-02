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

#include "ErrnoTest.h"

#include <cerrno>
#include <functional>

#include "tagitcommon/util/Errno.h"

namespace
{
void testGetErrnoError()
{
	vrfy::assert::assertTrue(tagit::util::getErrnoError(EINVAL).length() >
	                         0);
	vrfy::assert::assertTrue(tagit::util::getErrnoError(EBADF).length() >
	                         0);
}

void testThrowErrnoError()
{
	vrfy::assert::assertThrows([]()
	                           {
		                           tagit::util::throwErrnoError(EINVAL);
		                   });
	vrfy::assert::assertThrows([]()
	                           {
		                           tagit::util::throwErrnoError(EBADF);
		                   });
}
}

namespace tagit_test
{
namespace util
{
void ErrnoTest::test()
{
	testGetErrnoError();
	testThrowErrnoError();
}
}
}
