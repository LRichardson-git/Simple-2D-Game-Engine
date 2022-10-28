#include "Visulization.h"
#include "Sprite.h"
#include "Rectangle.h"

Visulization::Visulization()
{
}

Visulization::~Visulization()
{
	//loop through spritemap and delete them after program closes
	for (auto& p : m_SpriteMap)
		delete p.second;
}

bool Visulization::Initialise()
{	
	//initialise the screen 
	if (!HAPI.Initialise(m_Width, m_Height, "test")) {
		std::cerr << "could not initilise" << std::endl;
		return false;
	}
		

	m_screen = HAPI.GetScreenPointer();

	return true;
}

bool Visulization::CreateSprite(const std::string& filename, const std::string& name)
{ 
	//create a new sprite and put it into sprite map
	Sprite* newSprite = new Sprite;
	if (!newSprite->Load(filename)) {
		delete newSprite;
		return false;
	}

	m_SpriteMap[name] = newSprite;

	return true;
}

void Visulization::Clear_Screen()
{
	//clears the scren
	BYTE* temp{ HAPI.GetScreenPointer() };
	HAPI_TColour col (Red, Green, Blue);

	for (int i = 0; i < m_Width * m_Height; i++) {
		memcpy(temp, &col, 4);
		temp += 4;
	}
}

void Visulization::Change_Colour()
{
	//change colour values
	if (keyData.scanCode['R'] && Red < 255)
		Red++;
	else if (keyData.scanCode['B'] && Blue < 255)
		Blue++;
	else if (keyData.scanCode['G'] && Green < 255)
		Green++;

	//reset colours
	if (keyData.scanCode['T']) {
		Red = 0;
		Blue = 0;
		Green = 0;
	}

}

void Visulization::RenderFast(const std::string& name, int posX, int posY) //rendering goes in sprite
{
	if (m_SpriteMap.find(name) == m_SpriteMap.end())
		return; //put error message

	//quickly render 
	m_SpriteMap.at(name)->RenderFast(m_screen, m_Width, m_Height, posX, posY);
}

void Visulization::Render(const std::string& name, int posX, int posY, int FrameNumber) const
{

	//check to see if not at wrong location in spritemap
	if (m_SpriteMap.find(name) == m_SpriteMap.end())
		return; //put error message

	//create screen rectangle
	Rectangle screenRect(0, m_Width, 0, m_Height);

	//sent to renderfunction in sprite 
	m_SpriteMap.at(name)->RenderAnimation(m_screen, screenRect, posX, posY, FrameNumber, name);


	
}

int Visulization::getRect(const std::string& name, int ad)
{
	//get value of side of rectangle
	int SideValue = m_SpriteMap.at(name)->returnValue(ad);
	
	return SideValue;
}

