#include "Sprite.h"
#include "Rectangle.h"

Sprite::Sprite()
{
	
}

Sprite::~Sprite()
{
	delete[]m_data;
}

bool Sprite::Load(const std::string& filename)
{
	//load a texture
	if (!HAPI.LoadTexture(filename, &m_data, ms_Width, ms_Height)) {
		HAPI.UserMessage("texture could not load", "error");
		return false;
	}


	return true;
}



void Sprite::RenderAnimation(BYTE* dest, const Rectangle& destRect, int posX, int posY,int FrameNumber, std::string Entity)
{
	//calacualte the left and right sides of the rectangle for the correct frame
	int LeftSprite = SourceRectanglesides(Entity, FrameNumber, 2);
	int RightSprite = SourceRectanglesides(Entity, FrameNumber, 1);
	
	//create source Rectangle
	Rectangle sourceRect(0, ms_Width, 0, ms_Height);
	Rectangle clipped(sourceRect);

	if (clipped.CompletlyOutside(destRect))
		return;

	//translate
	clipped.Translate(posX, posY);
	clipped.ClipTo(destRect);
	clipped.Translate(-posX, -posY);

	posX = std::max(0, posX);
	posY = std::max(0, posY);

	//Changes sourceRectangel to correct dimensions for framenumber
	if (!FrameNumber == 0) {
		clipped.right = RightSprite;
		clipped.left = LeftSprite;

	}
	
	//copypaste the rectangle dimensions into variables to transfer to check collision
	left = clipped.left;
	right = clipped.right;
	top = clipped.top;
	bottom = clipped.bottom;

	//temporary bytes of screen and texture
	BYTE* temp = dest + (posX + (int64_t)posY * destRect.width()) * 4;
	BYTE* tex = m_data + (clipped.left  + (int64_t)clipped.top * sourceRect.width()) * 4;

	for (int y = 0; y < clipped.Height(); y++) {

		for (int x = 0; x < clipped.width(); x++) {
			//set sourcecolour and dest colour to the texture  colour and the screen colour
			
				HAPI_TColour* SourceColour = (HAPI_TColour*)tex;
				HAPI_TColour* destCol = (HAPI_TColour*)temp;


				//if the alpha is equal to 255 the destcol becomes the source colour (visible)
				if (SourceColour->alpha == 255)
					*destCol = *SourceColour;

				//if it isnt decide how transparent
				else if (SourceColour->alpha > 0) {

					float alpha = SourceColour->alpha / 255.0f;

					destCol->red = int(alpha * SourceColour->red + (1.0f - alpha) * destCol->red);
					destCol->blue = int(alpha * SourceColour->blue + (1.0f - alpha) * destCol->blue);
					destCol->green = int(alpha * SourceColour->green + (1.0f - alpha) * destCol->green);

				
			}

			temp += 4;
			tex += 4;
		}
		temp += ((int64_t)destRect.width() - clipped.width()) * 4;
		tex += ((int64_t)ms_Width - clipped.width()) * 4;
	}
	}



void Sprite::RenderFast(BYTE* screen, int ScreenWidth, int ScreenHeight, int posX, int posY)
{
	//temporary bytes of the screen and texture
	BYTE* tempScreen{ HAPI.GetScreenPointer() };
	BYTE* temp = tempScreen + (posX + (int64_t)posY * ScreenWidth) * 4;
	BYTE* tex{ m_data };



	//normal
	for (int i = 0; i < ms_Height; i++) {
		memcpy(temp, tex, (int64_t)ms_Width * 4);
		//move texture pointer to next line
		temp += (int64_t)ScreenWidth * 4;
		//move screen poitner to to next line
		tex += (int64_t)ms_Width * 4;

	}

}

int Sprite::SourceRectanglesides(std::string Entity, int frameNumb ,int ID)
{
	//if player entity this is how the dimensions for the spritesheet are handled
	if (Entity == "Player" && ID == 1) 
		return frameNumb * 65;

	if (Entity == "Player" && ID == 2)
		return  frameNumb * 65 - 65;

	if (Entity == "Enemy" && ID == 1)
		return frameNumb * 32;
	
	if (Entity == "Enemy" && ID == 2)
		return  frameNumb * 32 - 32;
}

int Sprite::returnValue(int ad)
{
	//couldn't figure out more elegant solution so simply gonna send the dimensions of the rectangle one at a time
	if (ad == 1)
		return left;

	if (ad == 2)
		return right;

	if (ad == 3)
		return top;

	if (ad == 4)
		return bottom;

	return 0;
}




void Sprite::ClipBlit(BYTE* dest, const Rectangle& destRect, int posX, int posY) // the one that is used
{
	Rectangle sourceRect(0, ms_Width, 0, ms_Height);
	Rectangle clipped(sourceRect);

	if (clipped.CompletlyOutside(destRect))
		return;

	clipped.Translate(posX, posY);
	clipped.ClipTo(destRect);
	clipped.Translate(-posX, -posY);

	posX = std::max(0, posX);
	posY = std::max(0, posY);

	//temporary bytes of screen and texture
	BYTE* temp = dest + (posX + (int64_t)posY * destRect.width()) * 4;
	BYTE* tex = m_data + (clipped.left + (int64_t)clipped.top * sourceRect.width()) * 4;

	for (int y = 0; y < clipped.Height(); y++) {

		for (int x = 0; x < clipped.width(); x++) {
			//set sourcecolour and dest colour to the texture  colour and the screen colour
			if (x < 100) {
				HAPI_TColour* SourceColour = (HAPI_TColour*)tex;
				HAPI_TColour* destCol = (HAPI_TColour*)temp;


				//if the alpha is equal to 255 the destcol becomes the source colour (visible)
				if (SourceColour->alpha == 255)
					*destCol = *SourceColour;

				//if it isnt decide how transparent
				else if (SourceColour->alpha > 0) {

					float alpha = SourceColour->alpha / 255.0f;


					destCol->red = int(alpha * SourceColour->red + (1.0f - alpha) * destCol->red);
					destCol->blue = int(alpha * SourceColour->blue + (1.0f - alpha) * destCol->blue);
					destCol->green = int(alpha * SourceColour->green + (1.0f - alpha) * destCol->green);

				}
			}
			

			
			temp += 4;
			tex += 4;
		}
		temp += ((int64_t)destRect.width() - clipped.width()) * 4;
		tex += ((int64_t)ms_Width - clipped.width()) * 4;
	}

}