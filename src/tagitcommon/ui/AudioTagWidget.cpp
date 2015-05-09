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

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

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
	return tag;
}
}
}
