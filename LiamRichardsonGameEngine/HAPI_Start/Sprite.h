#pragma once
#include <HAPI_lib.h>

using namespace HAPISPACE;
class Rectangle;

class Sprite
{
private:
	int ms_Height;
	int ms_Width;
	BYTE* m_data{ nullptr };

	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };
public:
	Sprite();
	~Sprite();

	bool Load(const std::string& filename);
	void RenderAnimation(BYTE* dest, const Rectangle& destRect, int posX, int posY, int FrameNumber, std::string Entity);
	void RenderFast(BYTE* screen, int ScreenWidth, int ScreenHeight, int posX, int posY);

	int SourceRectanglesides(std::string Entity, int frameNumb ,int ID);
	int returnValue(int ad);

	void ClipBlit(BYTE* dest, const Rectangle& destRect, int DesX, int DesY);
};

