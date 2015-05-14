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

#include "String.h"

#include <iterator>

namespace tagit
{
namespace string
{
void singleSpaced(QString &str)
{
	QString::iterator out = str.begin();
	QString::iterator in = str.begin();
	QString::iterator end = str.end();

	while(in != end)
	{
		if(!in->isSpace())
		{
			*(out++) = *(in++);
			continue;
		}

		*out = ' ';
		while(in->isSpace() && (in != end))
			++in;
		++out;
	}

	str.resize(str.size() - std::distance(out, end));
}
}
}
