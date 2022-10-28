#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{
public:
	EnemyEntity(std::string spriteName);
	~EnemyEntity();
	void Update() override final;
	ESide GetSide() const override final { return ESide::eEnemy; }
	int GetFrameNumber();

	//direction the enemies will go in is random
	int direction{ direction = rand() % 10 };
};

