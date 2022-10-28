#include "world.h"
#include "Visulization.h"
#include "EnemyEntity.h"

#include "PlayerEntity.h"
#include <cassert>
#include"BulletEntity.h"
#include "BulletEnemyEntity.h"


bool world::LoadLevel()
{
	//Load all the sprites

	//Create textures and load their sprites
	m_Viz->CreateSprite("data//PlayerPlane.tga", "Player");
		
	m_Viz->CreateSprite("data//bullet.tga", "background");

	m_Viz->CreateSprite("data//greenSpinner.tga", "Enemy");
		
	
	//create Player Entity
	PlayerEntity* newPlayer = new PlayerEntity("Player");
	m_entityVector.push_back(newPlayer);
	newPlayer->SetPosition(Vector2(400, 400));

	//Create enemy entities
	for (int i = 0; i < 6; i++) {
		//create the entity its name and the sprite that it is using
		EnemyEntity* newenemey = new EnemyEntity("Enemy");
		m_entityVector.push_back(newenemey);

		//set position
		newenemey->SetPosition(Vector2(900, 150 + (i * 75)));

	}
	 
	 //Create set of bullets for the player to use
	 for (int i = 0; i < 10; i++) {
		 BulletEntity* newBackground = new BulletEntity("background");
		 m_entityVector.push_back(newBackground);
		 newBackground->SetPosition(Vector2(0, 0));
		 i++;
	 }

	 //create a set of bullets for the enemies to use
	 for (int i = 0; i < 12; i++) {
		 BulletEnemyEntity* newBulletEnemy = new BulletEnemyEntity("background");
		 m_entityVector.push_back(newBulletEnemy);
		 newBulletEnemy->SetPosition(Vector2(0, 0));
		 i++;
	 }

	 //create background entity


	

	return true;
}

//Tick time is 50 milliseconds
constexpr DWORD TickTime{ 50 };

void world::Update()
{
	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update()) {

		
		//clear screen
		m_Viz->Clear_Screen();

		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
		if (timeSinceLastTick >= TickTime) {

			//loop through entities and update
			for (auto p : m_entityVector) {
				if(p->isAlive())
					p->Update();
					
				//check to see if entity wants to fire a bullet
					if (p->Firebullet()) {
						if (p->canFire())
							firebulletEnemy(p->GetPosition(), p->EsideNumber());
						//check to see if player wants to fire bullet but in intervals of time to limit shooting spam
						if (HAPI.GetTime() - m_lastTimeShot >= m_shootTime) {
							firebullet(p->GetPosition(),p->EsideNumber());
							m_lastTimeShot = HAPI.GetTime();
						}
					}
					
					
			}
			lastTimeTicked = HAPI.GetTime();
			
			//loop every entity but two at a time to compare to each other for collision
			for (size_t i = 0; i < m_entityVector.size(); i++) {
				for (size_t j = i + 1; j < m_entityVector.size(); j++) {
					m_entityVector[i]->CheckCollision(*m_Viz, *m_entityVector[j]); // check for i vs j
				}
					
			}
			//reset tick 
			timeSinceLastTick = 0;
		}
		
		//interpolation
		float s = timeSinceLastTick / (float)TickTime;
		assert(s >= 0 && s <= 1.0f);

		//render entities
		for (auto p : m_entityVector) {
			p->Render(*m_Viz, s);
			
		}
			

		
		//generate randomly generated background of "stars"
		background.StaryBackground(1200, 720);

	
	}

	
}
void world::firebullet(Vector2 pos, int side)
{
	//check the side to see if player
	if (side == 1) {
		//loop throuhg the entity vector
		for (auto p : m_entityVector) {
			//check to see if it is a bullet
			if (p->isBullet())
				//check to see if it is alive
				if (!p->isAlive()) {
					//if its not alive then check to see that it matches the side of the entity 
					// and if it does then make the bullet alive and set its position to the entity that wants to fire
					if (side == p->EsideNumber()) {
						p->alive();
						p->SetPosition(pos);
						return;
					}
				}
		}
	}
	return;
}

//basically the same as the function above it but for enemy entites
void world::firebulletEnemy(Vector2 pos, int side)
{
	if (side == 2) {
		for (auto p : m_entityVector) {
			if (p->isBullet())
				if (!p->isAlive()) {
					if (side == p->EsideNumber()) {
						p->alive();
						p->SetPosition(pos);
						return;
					}
					
				}
		}
	}
	return;
}



world::world()
{
}

world::~world()
{
	//delete the vizulation created
	delete m_Viz;
	
	//loop through and delete the entities inside of the entity vector to not create a memeory leack
	for (auto p : m_entityVector)
		delete p;
}


void world::Run()
{
	//create a vizulation and initalise a window
	m_Viz = new Visulization;
	if (!m_Viz->Initialise())
		return;

	//run load level and being update
	if (LoadLevel())
		Update();
}
