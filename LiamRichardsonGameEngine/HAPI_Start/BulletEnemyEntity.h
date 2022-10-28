#pragma once
#include "Entity.h"
class BulletEnemyEntity :
	public Entity
{
public:
	BulletEnemyEntity(std::string spriteName);
	~BulletEnemyEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::eEnemy; }

};

