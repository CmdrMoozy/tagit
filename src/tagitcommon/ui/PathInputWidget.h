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

#ifndef TAGITCOMMON_UI_PATH_INPUT_WIDGET_H
#define TAGITCOMMON_UI_PATH_INPUT_WIDGET_H

#include <initializer_list>
#include <map>

#include <QString>
#include <QWidget>

class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

namespace tagit
{
namespace ui
{
/*!
 * \brief Denotes the type of path a PathInputWidget should select.
 */
enum class PathInputType
{
	FILE,
	DIRECTORY
};

/*!
 * \brief This structure defines a path input's characteristics.
 */
struct PathInput
{
	std::string name;
	PathInputType type;
	QString label;

	PathInput(const std::string &n, PathInputType t, const QString &l);

	PathInput(const PathInput &) = default;
	PathInput &operator=(const PathInput &) = default;
};

/*!
 * \brief This widget provides a standard text / browse path input widget.
 */
class PathInputWidget : public QWidget
{
	Q_OBJECT

public:
	/*!
	 * \param inputs The list of path inputs to create.
	 * \param p This widget's parent widget.
	 * \param f The window flags for this widget.
	 */
	PathInputWidget(const std::initializer_list<PathInput> &inputs,
	                QWidget *p = nullptr, Qt::WindowFlags f = 0);

	/*!
	 * \param l The label for this path input widget.
	 * \param t The type of path to input.
	 * \param p This widget's parent widget.
	 * \param f The window flags for this widget.
	 */
	PathInputWidget(const QString &l, PathInputType t, QWidget *p = nullptr,
	                Qt::WindowFlags f = 0);

	PathInputWidget(const PathInputWidget &) = delete;
	virtual ~PathInputWidget() = default;

	PathInputWidget &operator=(const PathInputWidget &) = delete;

	/*!
	 * This function returns the currently selected path from a single
	 * path input widget. If this widget only contains one input, then
	 * that input's path is returned regardless of the name provided.
	 *
	 * \param The input name to retrieve the path from.
	 * \return This widget's currently selected path, as a string.
	 */
	QString getPath(const std::string &name = "") const;

private:
	QGridLayout *layout;
	std::map<const QLineEdit *, std::string> inputNames;
	std::map<const QPushButton *, PathInputType> inputTypes;
	std::map<const QPushButton *, QLineEdit *> buttonInputs;
	std::map<const QPushButton *, std::string> buttonNames;
	std::map<std::string, QLineEdit *> pathInputs;

private Q_SLOTS:
	void doPathInputChanged();

	void doBrowse();

Q_SIGNALS:
	void pathChanged(const std::string &, const QString &);
};
}
}

#endif
