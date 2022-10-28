#include "Rectangle.h"
#include "Visulization.h"
Rectangle::Rectangle(int left, int right, int top, int bottom) : left{ left }, right{ right }, top{ top }, bottom{ bottom }
{
}

Rectangle::~Rectangle()
{
}

bool Rectangle::CompletlyInside(const Rectangle& other)
{
	//check if completlty inside rectangle
	if (left < other.left)
		return false;

	if (top < other.top)
		return false;

	if (right > other.right)
		return false;

	if (bottom > other.bottom)
		return false;

	return true;
}

bool Rectangle::CompletlyOutside(const Rectangle& other)
{
	//check if completlty outside of a rectangle
	
	if (right < other.left)
		return true;
	if (bottom < other.top)
		return true;
	if (left > other.right)
		return true;

	if (top > other.bottom)
		return true;

	return false;
}

void Rectangle::ClipTo(const Rectangle& other)
{
	//clip to another rectangle
	left = std::max(left, other.left);
	right = std::min(right, other.right);
	top = std::max(top, other.top);
	bottom = std::min(bottom, other.bottom);

}

void Rectangle::Translate(int posX, int posY)
{
	//change the position of the rectangle
	bottom += posY;
	top += posY;
	right += posX;
	left += posX;

}

