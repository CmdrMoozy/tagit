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
#include <QWidget>

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
MainWindow::MainWindow() : QMainWindow(nullptr, 0), pathInputs(nullptr)
{
	setWindowTitle(tr("TagIt"));

	centralWidget = new QWidget(this);
	layout = new QGridLayout(centralWidget);

	pathInputs = new PathInputWidget(
	        {PathInput(LIBRARY_NAME, PathInputType::DIRECTORY,
	                   tr("Music library:")),
	         PathInput(INPUT_NAME, PathInputType::DIRECTORY,
	                   tr("Music to tag:"))},
	        centralWidget);

	layout->addWidget(pathInputs, 0, 0, 1, 1);
	layout->setRowStretch(1, 1);
	layout->setColumnStretch(1, 1);
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
}
}
}
