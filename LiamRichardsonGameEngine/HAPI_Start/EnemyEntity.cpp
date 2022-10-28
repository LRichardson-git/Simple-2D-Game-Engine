#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::string spriteName) : Entity(spriteName)
{
	//set valkues for th eneitty
	Health = 5;
	m_Eside = 2;
	m_DamageInflict = 50;
	m_numFrame = 8;

	//randomise speed of enemy
	m_speed = rand() % 10;
	firebullet = true;
	
	
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{

	//create position vector
	Vector2 pos{ GetPosition() };

	//chagne
	m_bullets = 0;
	

	//change direction of enemy depening on location
	if (pos.y > 680) 
		direction = 5;

	if (pos.y < 0)
		direction = 4;

	if (direction >=5)
		pos.y -= m_speed;

	if (direction <=4 )
		pos.y += m_speed;

	//so enemy moves toward player at slow pace
	pos.x -= 0.8f;

	//death 
	if (Health <= 0) {
		//moves off screen to make sure no issues occur while dead
		pos.x = -100;
		pos.y = -100;
		//cant collide or firebullets anymore
		m_alive = false;
		firebullet = false;
	}
	
	//set position
	SetPosition(pos);
}

int EnemyEntity::GetFrameNumber()
{
	//return the current frame number
	return m_frameNum;

}
