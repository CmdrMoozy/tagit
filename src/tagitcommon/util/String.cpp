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

#include <algorithm>
#include <iterator>
#include <utility>

#include "tagitcommon/util/asciiFilenameTranslationMap.h"
#include "tagitcommon/util/visualAsciiTranslationMap.h"

namespace
{
void translateString(QString &str,
                     const std::map<QChar, QString> &translationMap,
                     bool allowUnmapped)
{
	QString processed;
	processed.reserve(str.size());

	for(const QChar &c : str)
	{
		auto it = translationMap.find(c);
		if(it != translationMap.end())
			processed.append(it->second);
		else if(allowUnmapped)
			processed.append(c);
	}

	str = std::move(processed);
}
}

namespace tagit
{
namespace string
{
void visualTranslateToASCII(QString &str)
{
	translateString(str, detail::VISUAL_ASCII_TRANSLATION_MAP, true);
}

void translateASCIIToFilename(QString &str)
{
	translateString(str, detail::ASCII_FILENAME_TRANSLATION_MAP, false);
}

void singleSpace(QString &str)
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

void trim(QString &str)
{
	const QChar *it = nullptr;
	for(const QChar *i = str.data(); i != str.data() + str.length(); ++i)
	{
		if(!i->isSpace())
		{
			it = i;
			break;
		}
	}

	const QChar *revit = nullptr;
	for(const QChar *i = str.data() + (str.length() - 1); i >= str.data();
	    --i)
	{
		if(!i->isSpace())
		{
			revit = i;
			break;
		}
	}

	if((it == nullptr) || (revit == nullptr))
		return;

	str = QString(it, revit - it + 1);
}
}
}
