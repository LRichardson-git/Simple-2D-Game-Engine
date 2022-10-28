#include "PlayerEntity.h"
#include <HAPI_lib.h>
using namespace HAPISPACE;
PlayerEntity::PlayerEntity(std::string spriteName) : Entity(spriteName)
{
	Health = 10;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update()
{
	//keyboard data
	auto keyData{ HAPI.GetKeyboardData() };

	//Set frame number to 1 since it is defualt
	m_frameNum = 1;

	//create vector based on position
	Vector2 pos{ GetPosition() };
	

	//keyboard inputes for movement
	if (keyData.scanCode['W'] && m_alive == true) {
		//change framenumber if moving upwards
		m_frameNum = 2;
		pos.y -= m_speed;
	}
		
	if (keyData.scanCode['S']) {
		//change framenumber if moving downwards
		m_frameNum = 3;
		pos.y += m_speed;
	}
	
	if (keyData.scanCode['A'])
		pos.x -= m_speed;

	if (keyData.scanCode['D'])
		pos.x += m_speed;

	//check to see if player is trying to fire bullet
	if (keyData.scanCode['F'])
		firebullet = true;
	else
		firebullet = false;

	//death
	if (Health <= 0) {
		//cease ability to collide and fire bullets
		m_alive = false;
		firebullet = false;
		//move offscreen
		pos.x = -100;
		pos.y = -100;
	}
	//set position using previosly created position vector 
	SetPosition(pos);
	
}


