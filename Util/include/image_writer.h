#pragma once

#include <string>

class image_writer
{
public:
	static void save_png(const std::string& filename, int width, int height, int channels, const void* data);
	static void save_jpg(const std::string& filename, int width, int height, int channels, const void* data);
};