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

#include "FS.h"

#include <fstream>
#include <stdexcept>

#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <boost/filesystem.hpp>

#include "tagitcommon/util/Errno.h"

namespace tagit
{
namespace fs
{
std::string stripSymlink(const std::string &path)
{
	struct stat stats;
	int ret = stat(path.c_str(), &stats);
	if(ret != 0)
		return "";
	std::string stripped = path;
	if(S_ISLNK(stats.st_mode))
	{
		char buf[PATH_MAX];
		ssize_t length = readlink(path.c_str(), buf, PATH_MAX);
		if(length == -1)
			util::throwErrnoError();
		stripped.assign(buf,
		                static_cast<std::string::size_type>(length));
	}
	return stripped;
}

void createFile(const std::string &path)
{
	if(boost::filesystem::exists(boost::filesystem::path(path)))
		throw std::runtime_error("Path already exists.");

	std::ofstream stream(path.c_str(),
	                     std::ios_base::out | std::ios_base::binary);
	if(!stream.is_open())
		throw std::runtime_error("File creation failed.");
	stream.close();

	if(!boost::filesystem::exists(boost::filesystem::path(path)))
		throw std::runtime_error("File creation failed.");
}

void createSymlink(const std::string &target, const std::string &link)
{
	if(!boost::filesystem::exists(boost::filesystem::path(target)))
		throw std::runtime_error("Symlink target doesn't exist.");

	if(boost::filesystem::exists(boost::filesystem::path(link)))
		throw std::runtime_error("Symlink already exists.");

	int ret = symlink(target.c_str(), link.c_str());
	if(ret != 0)
		util::throwErrnoError();
}

bool isFile(const std::string &path)
{
	std::string stripped = stripSymlink(path);
	struct stat stats;
	int ret = stat(stripped.c_str(), &stats);
	if(ret != 0)
		util::throwErrnoError();
	return S_ISREG(stats.st_mode);
}

bool isExecutable(const std::string &path)
{
	std::string stripped = stripSymlink(path);
	return access(stripped.c_str(), X_OK) == 0;
}
}
}
