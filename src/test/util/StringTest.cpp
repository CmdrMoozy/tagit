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

#include <QString>

#include "tagitcommon/util/String.h"

namespace
{
void testVisualTranslateToASCII(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::visualTranslateToASCII(out);
	CHECK(QString(exp) == out);
}

void testTranslateASCIIToFilename(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::translateASCIIToFilename(out);
	CHECK(QString(exp) == out);
}

void testSingleSpaced(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::singleSpace(out);
	CHECK(QString(exp) == out);
}

void testTrim(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::trim(out);
	CHECK(QString(exp) == out);
}
}

TEST_CASE("Test visual ASCII translation", "[util]")
{
	testVisualTranslateToASCII(
	        " !\"#$%&'()*+,-./"
	        "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
	        "abcdefghijklmnopqrstuvwxyz{|}~cS(C)(R)"
	        "uAAAAAAAECEEEEIIIIDNOOOOOxOUUUUYSSaaaaaaaeceeeeiiiionoooooouuu"
	        "uyyAaAaAaCcCcCcCcDdDdEeEeEeEeEeGgGgGgGgHhHhIiIiIiIiIiIJijJjKkk"
	        "LlLlLlLlLlNnNnNnnNnOoOoOoOEoeRrRrRrSsSsSsSsTtTtTtUuUuUuUuUuUuW"
	        "wYyYZzZzZzbBBbBbOCcDDDdEFfGYHVIIKklNnOOoOIoiPpRtTtTUuVYyZzDZDz"
	        "dzLJLjljNJNjnjAaIiOoUuUuUuUuUuAaAaAEaeGgGgKkOoOojDZDzdzGgNnAaA"
	        "EaeOoAaAaEeEeIiIiOoOoRrRrUuUuSsTtHhNdZzAaEeOoOoOoOoYylntjACcLY"
	        "szBUEeJjQqRrYyBbDdFfMmPpSsTtWwWwWwYy",
	        " !\"#$%&'()*+,-./"
	        "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
	        "abcdefghijklmnopqrstuvwxyz{|}~"
	        "¢§©®µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùú"
	        "ûüýÿĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹ"
	        "ĺĻļĽľĿŀŁłŃńŅņŇňŉŊŋŌōŎŏŐőŒœŔŕŖŗŘřŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵŶŷ"
	        "ŸŹźŻżŽžƀƁƂƃƄƅƆƇƈƉƊƋƌƎƑƒƓƔƕƖƗƘƙƚƝƞƟƠơƢƣƤƥƦƫƬƭƮƯưƲƳƴƵƶǄǅǆǇǈǉǊǋǌǍ"
	        "ǎǏǐǑǒǓǔǕǖǗǘǙǚǛǜǞǟǠǡǢǣǤǥǦǧǨǩǪǫǬǭǰǱǲǳǴǵǸǹǺǻǼǽǾǿȀȁȂȃȄȅȆȇȈȉȊȋȌȍȎȏȐ"
	        "ȑȒȓȔȕȖȗȘșȚțȞȟȠȡȤȥȦȧȨȩȪȫȬȭȮȯȰȱȲȳȴȵȶȷȺȻȼȽȾȿɀɃɄɆɇɈɉɊɋɌɍɎɏḂḃḊḋḞḟṀṁ"
	        "ṖṗṠṡṪṫẀẁẂẃẄẅỲỳ");
}

TEST_CASE("Test ASCII to filename translation", "[util]")
{
	testTranslateASCIIToFilename(
	        " S And '() And  - 0123456789 - AtABCDEFGHIJKLMNOPQRSTUVWXYZ() "
	        "- abcdefghijklmnopqrstuvwxyz()",
	        " $&\'()+-0123456789:@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_"
	        "abcdefghijklmnopqrstuvwxyz{}");
}

TEST_CASE("Test single spacing algorithm", "[util]")
{
	testSingleSpaced("Я знаю, что вы ждали всю свою жизнь, и, наконец, "
	                 "ты здесь со мной сегодня вечером.",
	                 "Я знаю,     что вы ждали всю свою жизнь,\t\tи, "
	                 "наконец, ты\t \tздесь со \t мной сегодня вечером.");
}

TEST_CASE("Test trim algorithm", "[util]")
{
	testTrim("foo  \t  bar \n baz",
	         "\t\n\r \t\t foo  \t  bar \n baz\n\t     ");
}
