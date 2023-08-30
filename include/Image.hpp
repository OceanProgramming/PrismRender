#pragma once

#include "glm/glm.hpp"

#include <cstdint>

namespace PrismRender
{
	class Image
	{
	public:
		Image(int w, int h, int channels);
		Image(const char* pathToFile);

		int writeToFile(const char* filename);
		glm::vec3 getPixel(double u, double v) const;
		void resizeBuffer(int newWidth, int newHeight);
	
		int width;
		int height;
		int channels;
		uint8_t* buffer;
	};
}