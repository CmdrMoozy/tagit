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

#include "TemporaryStorage.h"

#include <stdexcept>

#include <boost/filesystem.hpp>

#include "tagitcommon/fs/FS.h"

namespace tagit
{
namespace fs
{
std::mutex TemporaryStorage::constructionMutex;

TemporaryStorage::TemporaryStorage(TemporaryStorageType t)
{
	static const std::string model = "tagit-%%%%-%%%%-%%%%-%%%%";

	std::lock_guard<std::mutex> lock(TemporaryStorage::constructionMutex);
	boost::filesystem::path base = boost::filesystem::temp_directory_path();
	boost::filesystem::path pathObj;
	do
	{
		pathObj = base / boost::filesystem::unique_path(model);
	} while(boost::filesystem::exists(pathObj));
	path = pathObj.string();

	switch(t)
	{
	case TemporaryStorageType::FILE:
		boost::filesystem::create_directories(pathObj.parent_path());
		createFile(pathObj.string());
		break;

	case TemporaryStorageType::DIRECTORY:
		boost::filesystem::create_directories(pathObj);
		break;

	default:
		throw std::runtime_error("Unimplemented storage type.");
	}
}

TemporaryStorage::~TemporaryStorage()
{
	boost::filesystem::path pathObj(path);
	boost::system::error_code ec;

	if(!boost::filesystem::exists(pathObj, ec))
		return;

	if(boost::filesystem::is_directory(pathObj, ec))
		boost::filesystem::remove_all(pathObj, ec);
	else
		boost::filesystem::remove(pathObj, ec);
}

std::string TemporaryStorage::getPath() const
{
	return path;
}
}
}
