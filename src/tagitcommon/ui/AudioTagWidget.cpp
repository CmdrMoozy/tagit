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

#include "AudioTagWidget.h"

#include <algorithm>
#include <stdexcept>

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

namespace
{
void setEditableComboBoxValue(QComboBox *comboBox, const QString &text)
{
	if(!comboBox->isEditable())
	{
		throw std::runtime_error(
		        "Only editable combo boxes are supported.");
	}

	int idx = comboBox->findText(text, Qt::MatchExactly);
	if(idx != -1)
		comboBox->setCurrentIndex(idx);
	else
		comboBox->setEditText(text);
}

uint64_t lineEditToUInt64(const QLineEdit *lineEdit)
{
	bool ok = false;
	qulonglong value = lineEdit->text().toULongLong(&ok, 10);
	if(!ok)
		return 0;
	return static_cast<uint64_t>(value);
}
}

namespace tagit
{
namespace ui
{
AudioTagWidget::AudioTagWidget(QWidget *p, Qt::WindowFlags f)
        : QWidget(p, f),
          tag(),
          layout(nullptr),
          titleLabel(nullptr),
          titleInput(nullptr),
          artistLabel(nullptr),
          artistInput(nullptr),
          albumLabel(nullptr),
          albumInput(nullptr),
          cdLabel(nullptr),
          cdInput(nullptr),
          yearLabel(nullptr),
          yearInput(nullptr),
          trackLabel(nullptr),
          trackInput(nullptr),
          trackOfLabel(nullptr),
          tracksInput(nullptr),
          genreLabel(nullptr),
          genreInput(nullptr)
{
	layout = new QGridLayout(this);

	titleLabel = new QLabel(tr("Title:"), this);
	titleInput = new QLineEdit(this);

	artistLabel = new QLabel(tr("Artist:"), this);
	artistInput = new QLineEdit(this);

	albumLabel = new QLabel(tr("Album:"), this);
	albumInput = new QLineEdit(this);

	cdLabel = new QLabel(tr("CD #:"), this);
	cdInput = new QSpinBox(this);
	cdInput->setRange(0, 99);

	yearLabel = new QLabel(tr("Year:"), this);
	yearInput = new QLineEdit(this);

	trackLabel = new QLabel(tr("Track #:"), this);
	trackInput = new QSpinBox(this);
	trackInput->setRange(0, 99);
	trackOfLabel = new QLabel(tr("of"), this);
	tracksInput = new QSpinBox(this);
	tracksInput->setRange(0, 99);

	genreLabel = new QLabel(tr("Genre:"), this);
	genreInput = new QComboBox(this);
	for(auto it = tagit::tag::util::TAG_GENRE_MAP_BEGIN;
	    it != tagit::tag::util::TAG_GENRE_MAP_END; ++it)
	{
		genreInput->addItem(QString(it->second.get()));
	}
	genreInput->setEditable(true);
	genreInput->setInsertPolicy(QComboBox::NoInsert);

	layout->addWidget(titleLabel, 0, 0, 1, 1);
	layout->addWidget(titleInput, 0, 1, 1, 5);
	layout->addWidget(artistLabel, 1, 0, 1, 1);
	layout->addWidget(artistInput, 1, 1, 1, 5);
	layout->addWidget(albumLabel, 2, 0, 1, 1);
	layout->addWidget(albumInput, 2, 1, 1, 3);
	layout->addWidget(cdLabel, 2, 4, 1, 1);
	layout->addWidget(cdInput, 2, 5, 1, 1);
	layout->addWidget(yearLabel, 3, 0, 1, 1);
	layout->addWidget(yearInput, 3, 1, 1, 1);
	layout->addWidget(trackLabel, 3, 2, 1, 1);
	layout->addWidget(trackInput, 3, 3, 1, 1);
	layout->addWidget(trackOfLabel, 3, 4, 1, 1);
	layout->addWidget(tracksInput, 3, 5, 1, 1);
	layout->addWidget(genreLabel, 4, 0, 1, 1);
	layout->addWidget(genreInput, 4, 1, 1, 5);
	layout->setColumnStretch(1, 1);
	layout->setRowStretch(5, 1);
	setLayout(layout);
}

tagit::tag::Tag AudioTagWidget::getTag() const
{
	apply();
	return tag;
}

void AudioTagWidget::setTag(const tagit::tag::Tag t)
{
	tag = t;
	titleInput->setText(tag.title);
	artistInput->setText(tag.artist);
	albumInput->setText(tag.album);
	cdInput->setValue(static_cast<int>(t.cd));
	yearInput->setText(QString("%1").arg(t.year));
	trackInput->setValue(static_cast<int>(t.track));
	tracksInput->setValue(static_cast<int>(t.tracks));
	setEditableComboBoxValue(genreInput, t.genre);
}

void AudioTagWidget::apply() const
{
	tag.title = titleInput->text();
	tag.artist = artistInput->text();
	tag.album = albumInput->text();
	tag.cd = static_cast<uint64_t>(cdInput->value());
	tag.year = lineEditToUInt64(yearInput);
	tag.track = static_cast<uint64_t>(trackInput->value());
	tag.tracks = static_cast<uint64_t>(tracksInput->value());
	tag.genre = genreInput->currentText();
}
}
}
