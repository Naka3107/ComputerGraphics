#include "image_writer.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void image_writer::save_png(const std::string& filename, int width, int height, int channels, const void* data)
{
	stbi_write_png(filename.c_str(), width, height, channels, data, 0);
}

void image_writer::save_jpg(const std::string& filename, int width, int height, int channels, const void * data)
{
	stbi_write_jpg(filename.c_str(), width, height, channels, data, 100);
}