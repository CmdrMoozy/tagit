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

#include "MainWindow.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QListView>
#include <QPushButton>
#include <QWidget>

#include "tagitcommon/audio/AudioFileModel.h"
#include "tagitcommon/ui/AudioTagWidget.h"
#include "tagitcommon/ui/PathInputWidget.h"

namespace
{
const std::string LIBRARY_NAME = "library";
const std::string INPUT_NAME = "input";
}

namespace tagit
{
namespace ui
{
MainWindow::MainWindow()
        : QMainWindow(nullptr, 0),
          pathsGroupBox(nullptr),
          pathsLayout(nullptr),
          pathInputs(nullptr),
          applyButton(nullptr),
          tracksGroupBox(nullptr),
          tracksLayout(nullptr),
          tracksView(nullptr),
          tracksModel(nullptr),
          tagGroupBox(nullptr),
          tagLayout(nullptr),
          tagWidget(nullptr)
{
	setWindowTitle(tr("TagIt"));

	centralWidget = new QWidget(this);
	layout = new QGridLayout(centralWidget);

	pathsGroupBox = new QGroupBox(tr("Input Paths"), centralWidget);
	pathsLayout = new QGridLayout(pathsGroupBox);
	pathInputs = new PathInputWidget(
	        {PathInput(LIBRARY_NAME, PathInputType::DIRECTORY,
	                   tr("Music library:")),
	         PathInput(INPUT_NAME, PathInputType::DIRECTORY,
	                   tr("Music to tag:"))},
	        pathsGroupBox);
	applyButton = new QPushButton(tr("Apply"), pathsGroupBox);
	pathsLayout->addWidget(pathInputs, 0, 0, 1, 2);
	pathsLayout->addWidget(applyButton, 1, 1, 1, 1);
	pathsLayout->setRowStretch(0, 1);
	pathsLayout->setColumnStretch(0, 1);
	pathsGroupBox->setLayout(pathsLayout);

	tracksGroupBox = new QGroupBox(tr("Audio Files"), centralWidget);
	tracksLayout = new QGridLayout(tracksGroupBox);
	tracksView = new QListView(tracksGroupBox);
	tracksModel = new tagit::audio::AudioFileModel(tracksView);
	tracksView->setModel(tracksModel);
	tracksLayout->addWidget(tracksView, 0, 0, 1, 1);
	tracksLayout->setRowStretch(0, 1);
	tracksLayout->setColumnStretch(0, 1);
	tracksGroupBox->setLayout(tracksLayout);

	tagGroupBox = new QGroupBox(tr("Audio File Tag"), centralWidget);
	tagLayout = new QGridLayout(tagGroupBox);
	tagWidget = new AudioTagWidget(tagGroupBox);
	tagLayout->addWidget(tagWidget, 0, 0, 1, 1);
	tagLayout->setRowStretch(0, 1);
	tagLayout->setColumnStretch(0, 1);
	tagGroupBox->setLayout(tagLayout);

	layout->addWidget(pathsGroupBox, 0, 0, 1, 1);
	layout->addWidget(tracksGroupBox, 1, 0, 1, 1);
	layout->addWidget(tagGroupBox, 0, 1, 2, 1);
	layout->setRowStretch(1, 1);
	layout->setColumnStretch(1, 1);
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);

	QObject::connect(applyButton, SIGNAL(clicked(bool)), this,
	                 SLOT(doApplyPaths()));
}

void MainWindow::doApplyPaths()
{
	std::string path = pathInputs->getPath(INPUT_NAME).toStdString();
	if(path.length() == 0)
		return;
	tracksModel->setPath(path);
}
}
}
