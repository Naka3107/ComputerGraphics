#include <vector>

#include "image_writer.h"

int main()
{
	int nx = 400;
	int ny = 300;

	std::vector<unsigned char> pixels;

	for (int j = 0; j < ny; j++)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;

			pixels.push_back(int(255.99 * r));
			pixels.push_back(int(255.99 * g));
			pixels.push_back(int(255.99 * b));
		}
	}

	image_writer::save_png("out.png", nx, ny, 3, pixels.data());

	return 0;
}