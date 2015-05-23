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

#include "TagTest.h"

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

	vrfy::assert::assertEquals(originalQString, convertedTagString);
	vrfy::assert::assertEquals(convertedTagString, roundedQString);
	vrfy::assert::assertEquals(originalTagString, convertedQString);
	vrfy::assert::assertEquals(convertedQString, roundedTagString);
}

void testStringConversion()
{
	testStringConversion("Test String");
}

void testGetFilename(const char *exp, const char *title, uint64_t track,
                     uint64_t cd = 1, uint64_t cds = 1)
{
	tagit::tag::Tag tag;
	tag.title = QString(title);
	tag.cd = cd;
	tag.track = track;

	vrfy::assert::assertEquals<QString>(exp, tag.getFilename(cds > 1));
}

void testGetFilename()
{
	testGetFilename("01 Such And Such", "Such & Such", 1);
	testGetFilename("01 Foo Bar", "Foo,   Bar", 1);
}
}

namespace tagit_test
{
namespace tag
{
void TagTest::test()
{
	testStringConversion();
	testGetFilename();
}
}
}
