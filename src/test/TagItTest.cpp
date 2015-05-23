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

#include <cstdlib>

#include <QApplication>

#include <Vrfy/Vrfy.h>

#include "test/audio/AudioFileTest.h"
#include "test/fs/EnvironmentTest.h"
#include "test/fs/FSTest.h"
#include "test/fs/TemporaryStorageTest.h"
#include "test/io/MemoryMappedFileTest.h"
#include "test/tag/TagTest.h"
#include "test/util/BitwiseTest.h"
#include "test/util/ErrnoTest.h"
#include "test/util/ScopeExitTest.h"
#include "test/util/StringTest.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv, false);

	vrfy::Tests tests;
	bool success = tests.add<tagit_test::fs::EnvironmentTest>()
	                       .add<tagit_test::audio::AudioFileTest>()
	                       .add<tagit_test::fs::FSTest>()
	                       .add<tagit_test::fs::TemporaryStorageTest>()
	                       .add<tagit_test::io::MemoryMappedFileTest>()
	                       .add<tagit_test::tag::TagTest>()
	                       .add<tagit_test::util::BitwiseTest>()
	                       .add<tagit_test::util::ErrnoTest>()
	                       .add<tagit_test::util::ScopeExitTest>()
	                       .add<tagit_test::util::StringTest>()
	                       .execute();

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
