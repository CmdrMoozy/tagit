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

#include "PathInputWidget.h"

#include <utility>

#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace tagit
{
namespace ui
{
PathInput::PathInput(const std::string &n, PathInputType t, const QString &l)
        : name(n), type(t), label(l)
{
}

PathInputWidget::PathInputWidget(const std::initializer_list<PathInput> &inputs,
                                 QWidget *p, Qt::WindowFlags f)
        : QWidget(p, f),
          layout(nullptr),
          inputNames(),
          inputTypes(),
          buttonInputs(),
          buttonNames(),
          pathInputs()
{
	layout = new QGridLayout(this);

	int i = 0;
	for(const auto &input : inputs)
	{
		// Skip inputs with duplicate names.
		if(pathInputs.find(input.name) != pathInputs.end())
			continue;

		QLabel *label = new QLabel(input.label, this);
		QLineEdit *pathInput = new QLineEdit(this);
		QPushButton *browseButton =
		        new QPushButton(tr("Browse..."), this);

		inputNames.insert(std::make_pair(pathInput, input.name));
		inputTypes.insert(std::make_pair(browseButton, input.type));
		buttonInputs.insert(std::make_pair(browseButton, pathInput));
		buttonNames.insert(std::make_pair(browseButton, input.name));
		pathInputs.insert(std::make_pair(input.name, pathInput));

		layout->addWidget(label, i, 0, 1, 1);
		layout->addWidget(pathInput, i, 1, 1, 1);
		layout->addWidget(browseButton, i, 2, 1, 1);
		++i;

		QObject::connect(pathInput,
		                 SIGNAL(textChanged(const QString &)), this,
		                 SLOT(doPathInputChanged()));
		QObject::connect(browseButton, SIGNAL(clicked(bool)), this,
		                 SLOT(doBrowse()));
	}

	layout->setColumnStretch(1, 1);
	layout->setRowStretch(i + 1, 1);
	setLayout(layout);
}

PathInputWidget::PathInputWidget(const QString &l, PathInputType t, QWidget *p,
                                 Qt::WindowFlags f)
        : PathInputWidget({PathInput("", t, l)}, p, f)
{
}

QString PathInputWidget::getPath(const std::string &name) const
{
	if(pathInputs.size() == 0)
		return QString();
	else if(pathInputs.size() == 1)
		return pathInputs.begin()->second->text();

	auto it = pathInputs.find(name);
	if(it == pathInputs.end())
		return QString();
	return it->second->text();
}

void PathInputWidget::doPathInputChanged()
{
	QLineEdit *input = dynamic_cast<QLineEdit *>(sender());
	if(input == nullptr)
		return;

	auto nit = inputNames.find(input);
	if(nit == inputNames.end())
		return;

	Q_EMIT(pathChanged(nit->second, input->text()));
}

void PathInputWidget::doBrowse()
{
	QPushButton *button = dynamic_cast<QPushButton *>(sender());
	if(button == nullptr)
		return;

	auto tit = inputTypes.find(button);
	if(tit == inputTypes.end())
		return;
	PathInputType type = tit->second;

	auto iit = buttonInputs.find(button);
	if(iit == buttonInputs.end())
		return;
	QLineEdit *input = iit->second;

	auto nit = buttonNames.find(button);
	if(nit == buttonNames.end())
		return;

	switch(type)
	{
	case PathInputType::FILE:
	{
		QString file = QFileDialog::getOpenFileName(
		        this, tr("Open File"), QDir::homePath());
		if(!file.isNull())
			input->setText(file);

		Q_EMIT(pathChanged(nit->second, file));
	}
	break;

	case PathInputType::DIRECTORY:
	{
		QString directory = QFileDialog::getExistingDirectory(
		        this, tr("Open Directory"), QDir::homePath());
		if(!directory.isNull())
			input->setText(directory);

		Q_EMIT(pathChanged(nit->second, directory));
	}
	break;

	default:
		break;
	};
}
}
}
