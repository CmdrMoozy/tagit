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

#include <catch/catch.hpp>

#include <string>

#include <QString>

#include <taglib/tstring.h>

#include "tagitcommon/tag/Tag.h"

namespace
{
void testStringConversion(const std::string &str)
{
	QString originalQString = QString::fromStdString(str);
	TagLib::String originalTagString(str);

	TagLib::String convertedQString =
	        tagit::tag::util::qstringToTagString(originalQString);
	QString convertedTagString =
	        tagit::tag::util::tagStringToQString(originalTagString);

	QString roundedQString =
	        tagit::tag::util::tagStringToQString(convertedQString);
	TagLib::String roundedTagString =
	        tagit::tag::util::qstringToTagString(convertedTagString);

	CHECK(originalQString == convertedTagString);
	CHECK(convertedTagString == roundedQString);
	CHECK(originalTagString == convertedQString);
	CHECK(convertedQString == roundedTagString);
}

void testGetFilename(const char *exp, const char *title, uint64_t track,
                     uint64_t cd = 1, uint64_t cds = 1)
{
	tagit::tag::Tag tag;
	tag.title = QString(title);
	tag.cd = cd;
	tag.track = track;

	CHECK(QString(exp) == tag.getFilename(cds > 1));
}
}

TEST_CASE("Test string encoding conversion", "[tag]")
{
	testStringConversion("Test String");
}

TEST_CASE("Test tag filename retrieval", "[tag]")
{
	testGetFilename("01 Such And Such", "Such & Such", 1);
	testGetFilename("01 Foo Bar", "Foo,   Bar", 1);
	testGetFilename("01 Test Title", "\tTest\tTitle\t", 1);
}
