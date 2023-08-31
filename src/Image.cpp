#include "../include/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../vendor/stb/stb_image_write.h"

#include <iostream>
#include <algorithm>

namespace PrismRender
{
	Image::Image(int w, int h, int c)
	{
		width = w;
		height = h;
		channels = c;
		buffer = new uint8_t[width * height * channels];
	}

	Image::Image(const char* filename)
	{
		stbi_info(filename, &width, &height, &channels);
		buffer = new uint8_t[width * height * channels];
		buffer = stbi_load(filename, &width, &height, &channels, 0);
	}

	int Image::writeToFile(const char* filename)
	{
		if (stbi_write_png(filename, width, height, channels, buffer, width * channels))
		{
			return 1;
		}
		std::cerr << "[Error] Writing image to file '" << filename << "' failed" << std::endl;
		return 0;
	}

	glm::vec3 Image::getPixel(float u, float v) const
	{
		int x = std::clamp(static_cast<int>(u * width), 0, width - 1);
		int y = std::clamp(static_cast<int>(v * height), 0, height - 1);
		size_t i = (x + y * width) * channels;
		return glm::vec3(buffer[i], buffer[i + 1], buffer[i + 2]) / 255.0f;
	}

	void Image::resizeBuffer(int newWidth, int newHeight)
	{
		width = newWidth;
		height = newHeight;
		if (buffer)
		{
			delete[] buffer;
		}
		buffer = new uint8_t[newWidth * newHeight * channels];
	}
}