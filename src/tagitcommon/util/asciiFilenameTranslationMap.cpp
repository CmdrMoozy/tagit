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

#include "asciiFilenameTranslationMap.h"

namespace tagit
{
namespace string
{
namespace detail
{
const std::map<QChar, QString> ASCII_FILENAME_TRANSLATION_MAP = {{' ', " "},
                                                                 {'$', "S"},
                                                                 {'&', " And "},
                                                                 {'\'', "'"},
                                                                 {'(', "("},
                                                                 {')', ")"},
                                                                 {'+', " And "},
                                                                 {'-', " - "},
                                                                 {'0', "0"},
                                                                 {'1', "1"},
                                                                 {'2', "2"},
                                                                 {'3', "3"},
                                                                 {'4', "4"},
                                                                 {'5', "5"},
                                                                 {'6', "6"},
                                                                 {'7', "7"},
                                                                 {'8', "8"},
                                                                 {'9', "9"},
                                                                 {':', " - "},
                                                                 {'@', "At"},
                                                                 {'A', "A"},
                                                                 {'B', "B"},
                                                                 {'C', "C"},
                                                                 {'D', "D"},
                                                                 {'E', "E"},
                                                                 {'F', "F"},
                                                                 {'G', "G"},
                                                                 {'H', "H"},
                                                                 {'I', "I"},
                                                                 {'J', "J"},
                                                                 {'K', "K"},
                                                                 {'L', "L"},
                                                                 {'M', "M"},
                                                                 {'N', "N"},
                                                                 {'O', "O"},
                                                                 {'P', "P"},
                                                                 {'Q', "Q"},
                                                                 {'R', "R"},
                                                                 {'S', "S"},
                                                                 {'T', "T"},
                                                                 {'U', "U"},
                                                                 {'V', "V"},
                                                                 {'W', "W"},
                                                                 {'X', "X"},
                                                                 {'Y', "Y"},
                                                                 {'Z', "Z"},
                                                                 {'[', "("},
                                                                 {']', ")"},
                                                                 {'_', " - "},
                                                                 {'a', "a"},
                                                                 {'b', "b"},
                                                                 {'c', "c"},
                                                                 {'d', "d"},
                                                                 {'e', "e"},
                                                                 {'f', "f"},
                                                                 {'g', "g"},
                                                                 {'h', "h"},
                                                                 {'i', "i"},
                                                                 {'j', "j"},
                                                                 {'k', "k"},
                                                                 {'l', "l"},
                                                                 {'m', "m"},
                                                                 {'n', "n"},
                                                                 {'o', "o"},
                                                                 {'p', "p"},
                                                                 {'q', "q"},
                                                                 {'r', "r"},
                                                                 {'s', "s"},
                                                                 {'t', "t"},
                                                                 {'u', "u"},
                                                                 {'v', "v"},
                                                                 {'w', "w"},
                                                                 {'x', "x"},
                                                                 {'y', "y"},
                                                                 {'z', "z"},
                                                                 {'{', "("},
                                                                 {'}', ")"}};
}
}
}