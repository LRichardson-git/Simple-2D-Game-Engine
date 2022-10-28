#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <unordered_map>
#include <string>

using namespace HAPISPACE;

class Sprite;

class Visulization
{
private:
	//Screen Dimensions
	int m_Width{ 1024 };
	int m_Height{ 720 };
	BYTE* m_screen{ nullptr };

	//Background colours
	int Red{ 0 };
	int Green{ 0 };
	int Blue{ 0 };
	HAPI_TColour col;

	//spritemap
	std::unordered_map<std::string, Sprite*> m_SpriteMap;

	//misc
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
public:
	//constructors
	Visulization();
	~Visulization();

	//initialistion
	bool Initialise();
	bool CreateSprite(const std::string& filename, const std::string& name);

	//Screen
	void Clear_Screen();
	void Change_Colour();

	//rendering
	void RenderFast(const std::string& name, int posX, int posY);
	void Render(const std::string& name, int posX, int posY, int FrameNumber) const;

	// yes
	int getRect(const std::string& name, int ad);

	//Stars
};

