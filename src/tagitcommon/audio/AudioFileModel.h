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

#ifndef TAGITCOMMON_AUDIO_AUDIO_FILE_MODEL_H
#define TAGITCOMMON_AUDIO_AUDIO_FILE_MODEL_H

#include <vector>

#include <QAbstractListModel>

#include "tagitcommon/audio/AudioFile.h"

namespace tagit
{
namespace audio
{
class AudioFileModel : public QAbstractListModel
{
public:
	AudioFileModel(QObject *p = nullptr);
	AudioFileModel(const std::string &path, QObject *p = nullptr);

	AudioFileModel(const AudioFileModel &) = delete;
	virtual ~AudioFileModel() = default;

	AudioFileModel &operator=(const AudioFileModel &) = delete;

	void setPath(const std::string &path);

	int rowCount(const QModelIndex &p = QModelIndex()) const;

	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const;
	QVariant data(const QModelIndex &i, int role = Qt::DisplayRole) const;

	const AudioFile &fileAt(const QModelIndex &i) const;

private:
	std::vector<AudioFile> files;

	void loadFiles(const std::string &path, bool signals = false);
};
}
}

#endif
