#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string spriteName) : Entity(spriteName)
{
	//set values
	m_isBullet = true;
	m_alive = false;
	m_DamageInflict = 10;
	m_Eside = 1;
	
}

BulletEntity::~BulletEntity()
{
	
}

void BulletEntity::Update()
{
	//create position vector of based of current position
	Vector2 pos{ GetPosition() };

	//moves to the right
	pos.x += m_speed;

	//death
	if (Health <= 0) {
		//goes off screen to avoid any possible complication
		pos.x = -100;
		pos.y = -100;
		m_alive = false;
	}
	//set position
	SetPosition(pos);

	//kill if goes off screen
	if (pos.x > 1000)
		Health = 0;
}
