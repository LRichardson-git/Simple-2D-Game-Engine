#pragma once
#include <algorithm>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Rectangle
{
public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

public:
	Rectangle(int left, int right, int top, int bottom);
	~Rectangle();
	
	int width() const { return right - left; }
	int Height() const { return bottom - top; }
	bool CompletlyInside(const Rectangle& other);
	bool CompletlyOutside(const Rectangle& other);
	void ClipTo(const Rectangle& other);
	void Translate(int posX, int posY);
	
};

