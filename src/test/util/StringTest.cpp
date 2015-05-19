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

#include "StringTest.h"

#include <QString>

#include "tagitcommon/util/String.h"

namespace
{
void testSingleSpaced(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::singleSpace(out);
	vrfy::assert::assertEquals<QString>(exp, out);
}

void testSingleSpaced()
{
	testSingleSpaced("Я знаю, что вы ждали всю свою жизнь, и, наконец, "
	                 "ты здесь со мной сегодня вечером.",
	                 "Я знаю,     что вы ждали всю свою жизнь,\t\tи, "
	                 "наконец, ты\t \tздесь со \t мной сегодня вечером.");
}

void testVisualTranslateToASCII(const char *exp, const char *in)
{
	QString out(in);
	tagit::string::visualTranslateToASCII(out);
	vrfy::assert::assertEquals<QString>(exp, out);
}

void testVisualTranslateToASCII()
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
}

namespace tagit_test
{
namespace util
{
void StringTest::test()
{
	testSingleSpaced();
	testVisualTranslateToASCII();
}
}
}
