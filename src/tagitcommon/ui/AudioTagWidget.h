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

#ifndef TAGITCOMMON_UI_AUDIO_TAG_WIDGET_H
#define TAGITCOMMON_UI_AUDIO_TAG_WIDGET_H

#include <QWidget>

#include "tagitcommon/tag/Tag.h"

class QComboBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QSpinBox;

namespace tagit
{
namespace ui
{
class AudioTagWidget : public QWidget
{
	Q_OBJECT

public:
	AudioTagWidget(QWidget *p = nullptr, Qt::WindowFlags f = 0);

	AudioTagWidget(const AudioTagWidget &) = delete;
	virtual ~AudioTagWidget() = default;

	AudioTagWidget &operator=(const AudioTagWidget &) = delete;

	tagit::tag::Tag getTag() const;
	void setTag(const tagit::tag::Tag t);

private:
	mutable tagit::tag::Tag tag;

	QGridLayout *layout;
	QLabel *titleLabel;
	QLineEdit *titleInput;
	QLabel *artistLabel;
	QLineEdit *artistInput;
	QLabel *albumLabel;
	QLineEdit *albumInput;
	QLabel *cdLabel;
	QSpinBox *cdInput;
	QLabel *yearLabel;
	QLineEdit *yearInput;
	QLabel *trackLabel;
	QSpinBox *trackInput;
	QLabel *trackOfLabel;
	QSpinBox *tracksInput;
	QLabel *genreLabel;
	QComboBox *genreInput;

	void apply() const;
};
}
}

#endif
