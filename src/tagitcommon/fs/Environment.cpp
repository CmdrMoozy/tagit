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

#include "Environment.h"

#include <cstdlib>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "tagitcommon/fs/FS.h"

namespace tagit
{
namespace fs
{
std::vector<std::string> getSystemPath()
{
	std::string path(getenv("PATH"));
	std::vector<std::string> components;
	boost::algorithm::split(components, path, boost::is_any_of(":"));
	return components;
}

std::experimental::optional<std::string> which(const std::string &command)
{
	if(command.find('/') != std::string::npos)
	{
		if(isFile(command) && isExecutable(command))
			return command;

		return std::experimental::nullopt;
	}

	std::vector<std::string> components = getSystemPath();
	for(const std::string &component : components)
	{
		std::string path = component;
		if(path[path.length() - 1] != '/')
			path.append("/");
		path.append(command);
		if(isFile(path) && isExecutable(path))
			return path;
	}

	return std::experimental::nullopt;
}
}
}
