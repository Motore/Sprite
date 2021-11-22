#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include <cassert>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	const bool reversed = height < 0;
	const bool is32b = bmInfoHeader.biBitCount == 32;

	if (reversed)
	{
		height = -height;
	}

	pPixel = new Color[width * height];

	file.seekg(bmFileHeader.bfOffBits);

	const int padding = (4 - (width * 3) % 4) % 4;


	if (!reversed)
	{
		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				/*if (reversed)
				{
					y = -y;
				}*/
				PutPixel(x, y, Color(file.get(), file.get(), file.get()));
				if (is32b)
				{
					file.seekg(1, std::ios::cur);
				}
			}
			if (!is32b)
			{
				file.seekg(padding, std::ios::cur);
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				PutPixel(x, y, Color(file.get(), file.get(), file.get()));
				if (is32b)
				{
					file.seekg(1, std::ios::cur);
				}
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

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
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	pPixel[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
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
