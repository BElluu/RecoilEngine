/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#pragma once

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include <zlib.h>

#include "demofile.h"

std::vector<std::string> GetDemoFileExtensions();

inline bool IsDemoExtension(const std::string& ext)
{
	const auto extensions = GetDemoFileExtensions();
	return std::find(extensions.begin(), extensions.end(), ext) != extensions.end();
}

inline bool ContentsLookLikeAReplay(const std::string& path)
{
	gzFile file = gzopen(path.c_str(), "rb");
	if (file == nullptr)
		return false;
	char magic[16] = {};
	const int bytesRead = gzread(file, magic, sizeof(magic));
	gzclose(file);
	return (bytesRead == static_cast<int>(sizeof(magic)) && memcmp(magic, DEMOFILE_MAGIC, sizeof(magic)) == 0);
}
