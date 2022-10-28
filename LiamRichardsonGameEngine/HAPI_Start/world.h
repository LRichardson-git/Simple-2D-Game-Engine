#pragma once
#include "Visulization.h"
#include <vector>
#include "Simulation.h"
#include "Entity.h"
class Entity;
class world
{
private:
	//simulation class created for the background
	Simulation background;

	//create a vizulation class and a empty vector for the entity class
	Visulization*m_Viz{ nullptr };
	std::vector<Entity*> m_entityVector;

	//create values for code inside of update
	DWORD m_lastTimeShot{ 0 };
	DWORD  m_shootTime{ 100 };
	//functions used by world in update
	bool LoadLevel();
	void Update();
public:
	world();
	~world();

	//Functions that fire bullet entities from the player and enemy
	void firebullet(Vector2 pos, int side);
	void world::firebulletEnemy(Vector2 pos, int side);

	void Run();
};

