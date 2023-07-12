#include "../include/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

Image::Image(int w, int h, int c)
{
	width = w;
	height = h;
	channels = c;
	buf = new uint8_t[width * height * channels];
}

Image::Image(const char* filename)
{
	stbi_info(filename, &width, &height, &channels);
	buf = new uint8_t[width * height * channels];
	buf = stbi_load(filename, &width, &height, &channels, 0);
}

int Image::save(const char* filename)
{
	if (stbi_write_png(filename, width, height, channels, buf, width * channels))
	{
		return 1;
	}
	return 0;
}

Vector3 Image::getPixel(double u, double v) const
{
	int x = u * width;
	int y = v * height;
	int i = (x + width * y) * 3;
	return Vector3(buf[i], buf[i+1], buf[i+2]) / 255.0;
}
