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

#include "AudioFileModel.h"

#include <stdexcept>
#include <utility>

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

namespace tagit
{
namespace audio
{
AudioFileModel::AudioFileModel(QObject *p) : QAbstractListModel(p), files()
{
}

AudioFileModel::AudioFileModel(const std::string &path, QObject *p)
        : QAbstractListModel(p), files()
{
	loadFiles(path);
}

void AudioFileModel::setPath(const std::string &path)
{
	loadFiles(path, true);
}

int AudioFileModel::rowCount(const QModelIndex &) const
{
	return files.size();
}

QVariant AudioFileModel::headerData(int, Qt::Orientation, int) const
{
	return QVariant();
}

QVariant AudioFileModel::data(const QModelIndex &i, int role) const
{
	auto idx = static_cast<decltype(files)::size_type>(i.row());

	switch(role)
	{
	case Qt::DisplayRole:
		return QVariant(
		        QString::fromStdString(files[idx].getFilename()));

	default:
		return QVariant();
	}
}

void AudioFileModel::loadFiles(const std::string &path, bool signals)
{
	bool nonempty = files.size() > 0;
	if(nonempty)
	{
		if(signals)
			beginRemoveRows(QModelIndex(), 0, files.size() - 1);

		files.clear();

		if(signals)
			endRemoveRows();
	}

	QFileInfo dirInfo(QString::fromStdString(path));
	if(!dirInfo.exists() || !dirInfo.isDir())
	{
		throw std::runtime_error(
		        "Must construct AudioFileModel from directory path.");
	}

	std::vector<AudioFile> newFiles;
	QDirIterator iterator(dirInfo.dir(), QDirIterator::Subdirectories);
	while(iterator.hasNext())
	{
		QString filePath = iterator.next();
		QFileInfo info(filePath);
		if(!info.isFile())
			continue;

		AudioFile file(info.absoluteFilePath().toStdString());
		if(!file)
			continue;
		newFiles.resize(newFiles.size() + 1);
		newFiles.back() = std::move(file);
	}

	if(signals)
		beginInsertRows(QModelIndex(), 0, newFiles.size() - 1);

	files = std::move(newFiles);

	if(signals)
		endInsertRows();
}
}
}
