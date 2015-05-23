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

#ifndef TAGITCOMMON_UTIL_STRING_H
#define TAGITCOMMON_UTIL_STRING_H

#include <QString>

namespace tagit
{
namespace string
{
/*!
 * This function translates the given string to ASCII "visually". That is,
 * non-ASCII characters are replaced with those ASCII characters which are
 * most visually similar to the input character. This means that marks like
 * umlauts and accents and etc. are removed.
 *
 * The resulting string is not intended to be equivalent, but merely to look
 * visually similar.
 *
 * Any unrecognized characters which can't be easily translated will merely
 * be removed.
 *
 * \param str The string to process.
 */
void visualTranslateToASCII(QString &str);

/*!
 * This function translates the given ASCII string to a string which is
 * suitable for filenames. Some characters will be replaced (e.g., '&'
 * becomes "And"), and other invalid characters will merely be omitted (e.g.,
 * '\n'.
 *
 * If the given string could contain non-ASCII characters,
 * visualTranslateToASCII should be called on the string first.
 *
 * NOTE: This function can insert extra spaces into the given string. After
 * calling this function, singleSpaced and trim should be called.
 *
 * \param str The string to process.
 */
void translateASCIIToFilename(QString &str);

/*!
 * This function alters the given string such that it contains only normal
 * ASCII space characters (' '), and that any series of more than one space
 * is replaced with only a single space.
 *
 * \param str The string to alter.
 */
void singleSpace(QString &str);

/*!
 * This function trims the given string, by removing any leading or trailing
 * whitespace from the string.
 *
 * \param str The string to alter.
 */
void trim(QString &str);
}
}

#endif
