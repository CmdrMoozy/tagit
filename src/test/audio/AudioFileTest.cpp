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

#include <fstream>

#include <QByteArray>
#include <QFile>
#include <QString>

#include "tagitcommon/audio/AACFile.h"
#include "tagitcommon/audio/ALACFile.h"
#include "tagitcommon/audio/AudioFile.h"
#include "tagitcommon/audio/FLACFile.h"
#include "tagitcommon/audio/MP3File.h"
#include "tagitcommon/audio/VorbisFile.h"
#include "tagitcommon/audio/WaveFile.h"
#include "tagitcommon/fs/TemporaryStorage.h"

namespace
{
template <typename FileType> void testAudioFile(const std::string &name)
{
	// Copy the file being tested to a temporary location.
	tagit::fs::TemporaryStorage temp(tagit::fs::TemporaryStorageType::FILE);
	QString path(":/data/");
	path.append(QString::fromStdString(name));
	QFile file(path);
	CHECK(file.open(QIODevice::ReadOnly));
	{
		QByteArray contents = file.readAll();
		std::ofstream out(temp.getPath(),
		                  std::ios_base::out | std::ios_base::binary);
		CHECK(out.is_open());
		out.write(contents.constData(), contents.length());
		out.flush();
		out.close();
	}

	// Construct an AudioFile from the temp file, and verify its type.
	tagit::audio::AudioFile audioFile(temp.getPath());
	CHECK(audioFile.is<FileType>());
}
}

TEST_CASE("Test audio file type detection", "[audio]")
{
	testAudioFile<tagit::audio::AACFile>("aac.m4a");
	testAudioFile<tagit::audio::AACFile>("aac-tagged.m4a");
	testAudioFile<tagit::audio::ALACFile>("alac.m4a");
	testAudioFile<tagit::audio::ALACFile>("alac-tagged.m4a");
	testAudioFile<tagit::audio::FLACFile>("flac.flac");
	testAudioFile<tagit::audio::FLACFile>("flac-tagged.flac");
	testAudioFile<tagit::audio::MP3File>("mp3-320.mp3");
	testAudioFile<tagit::audio::MP3File>("mp3-v0.mp3");
	testAudioFile<tagit::audio::MP3File>("mp3-v2.mp3");
	testAudioFile<tagit::audio::MP3File>("mp3-320-id3.mp3");
	testAudioFile<tagit::audio::VorbisFile>("vorbis.ogg");
	testAudioFile<tagit::audio::VorbisFile>("vorbis-tagged.ogg");
	testAudioFile<tagit::audio::WaveFile>("wav.wav");
}
