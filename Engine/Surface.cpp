#include "Surface.h"

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixel(new Color[width*height])
{
}

Surface::Surface(const Surface& surf)
	:
	Surface(surf.width, surf.height)
{
	for (int i = 0; i < width * height; i++)
	{
		pPixel[i] = surf.pPixel[i];
	}
}

Surface& Surface::operator=(const Surface& surf)
{
	width = surf.width;
	height = surf.height;

	delete[] pPixel;
	pPixel = new Color[width * height];
	for (int i = 0; i < width * height; i++)
	{
		pPixel[i] = surf.pPixel[i];
	}
	return *this;
}

Surface::~Surface()
{
	delete[] pPixel;
	pPixel = nullptr;
}

void Surface::PutPixel(int x, int y, Color c)
{
	pPixel[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	return pPixel[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
