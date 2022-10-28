#include "BulletEnemyEntity.h"

BulletEnemyEntity::BulletEnemyEntity(std::string spriteName) : Entity(spriteName)
{
	//set inital values
	m_isBullet = true;
	m_alive = false;
	m_DamageInflict = 10;
	m_Eside = 2;
}

BulletEnemyEntity::~BulletEnemyEntity()
{
}

void BulletEnemyEntity::Update()
{
	
	//create position vector based off of position
	Vector2 pos{ GetPosition() };

	m_bullets = 0;

	//move towards the left of the screen
	pos.x -= m_speed;

	//deathj
	if (Health <= 0) {
		pos.x = -100;
		pos.y = -100;
		m_alive = false;
	}

	//set position
	SetPosition(pos);

	//kill bullet if off screen
	if (pos.x < 0)
		Health = 0;
}
