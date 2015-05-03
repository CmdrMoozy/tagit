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

#include "test/fs/EnvironmentTest.h"
#include "test/fs/FSTest.h"
#include "test/fs/TemporaryStorageTest.h"
#include "test/util/ErrnoTest.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv, false);

	vrfy::Tests tests;
	tests.add<tagit_test::fs::EnvironmentTest>()
	        .add<tagit_test::fs::FSTest>()
	        .add<tagit_test::fs::TemporaryStorageTest>()
	        .add<tagit_test::util::ErrnoTest>()
	        .execute();

	return 0;

	return EXIT_SUCCESS;
}
