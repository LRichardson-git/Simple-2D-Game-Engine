#include "Simulation.h"

Simulation::Simulation()
{
	for (int i = 0; i < (KnumberStars); i++) {
		Rand_Star(i);
	}
}

Simulation::~Simulation()
{
}

void Simulation::Star_Pos(int Width, int Height)
{
	/*
	*/
	int Cx = Width / 2;
	int Cy = Height / 2;

	//Change EyeDistance
	if (keyData.scanCode['C'] && EyeDistance < EyeMax)
		EyeDistance = EyeDistance + 1;

	if (keyData.scanCode['V'] && EyeDistance > EyeMin)
		EyeDistance = EyeDistance - 1;


	for (int i = 0; i < (KnumberStars); i++) {

		//Calculate Star Position
		StarArray[i].Sx = ((EyeDistance * (StarArray[i].x - Cx)) / (EyeDistance + StarArray[i].z)) + Cx;
		StarArray[i].Sy = ((EyeDistance * (StarArray[i].y - Cy)) / (EyeDistance + StarArray[i].z)) + Cy;

		//reset star when out of screen
		if (StarArray[i].z <= 0.5) {
			Rand_Star(i);
		}

		//Calulate Star Position and render on screen
		offset = (StarArray[i].Sx + StarArray[i].Sy * Width) * 4;
		BYTE* pnter = HAPI.GetScreenPointer() + offset;
		HAPI_TColour col(255, 255, 255);
		memcpy(pnter, &col, 4);

		//Rate at which star gets closer to user
		StarArray[i].z = StarArray[i].z - 0.3f;
	}
}

void Simulation::Rand_Star(int i)
{
	StarArray[i].x = rand() % 1000;
	StarArray[i].y = rand() % 600;
	StarArray[i].z = rand() % 500;
}

void Simulation::StaryBackground(int Width, int Height)
{
	//used to create the starry background of the demo

	for (int i = 0; i < (KnumberStars); i++) {


		//reset star when out of screen
		if (StarArray[i].x < 0) {
			Rand_Star(i);
		}

		//Calulate Star Position and render on screen
		offset = (StarArray[i].x + StarArray[i].y * Width) * 4;
		BYTE* pnter = HAPI.GetScreenPointer() + offset;
		HAPI_TColour col(255, 255, 255);
		memcpy(pnter, &col, 4);

		//Rate at which star gets closer to user
		StarArray[i].x = StarArray[i].x - 1;
	}

}

