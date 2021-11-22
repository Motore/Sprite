#pragma once

#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface& surf);
	Surface& operator=(const Surface& surf);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	int width;
	int height;
	Color* pPixel = nullptr;
};