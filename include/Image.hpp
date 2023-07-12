#pragma once

#include <cstdint>

#include "../include/Vector3.hpp"

class Image
{
public:
	int width;
	int height;
	int channels;
	uint8_t* buf;

	Image(int w, int h, int channels);
	Image(const char* filename);

	int save(const char* filename);
	Vector3 getPixel(double u, double v) const;
};
