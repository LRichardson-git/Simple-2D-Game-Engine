#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;
class Simulation
{
private:
	//Star numbers
	const int KnumberStars = 1000;
	int EyeDistance = 100;
	int EyeMax = 500;
	int EyeMin = 10;
	unsigned int offset;
	
	struct StarPosition
	{
		int x;
		int y;
		int z;
		int Sx;
		int Sy;
	};


	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	StarPosition StarArray[1000];
public:
	Simulation();
	~Simulation();

	void Star_Pos(int Width, int Height);
	void Rand_Star(int i);

	void StaryBackground(int Width, int Height);
};

