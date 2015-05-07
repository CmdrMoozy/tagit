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

#ifndef TEST_AUDIO_AUDIO_FILE_TEST_H
#define TEST_AUDIO_AUDIO_FILE_TEST_H

#include <Vrfy/Vrfy.h>

namespace tagit_test
{
namespace audio
{
class AudioFileTest : public vrfy::Test
{
public:
	AudioFileTest() = default;
	virtual ~AudioFileTest() = default;

	virtual void test() override;
};
}
}

#endif