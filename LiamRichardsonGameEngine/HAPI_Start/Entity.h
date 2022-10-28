#pragma once

#include "Vector2.h"
#include <string>
#include "Rectangle.h"

enum class ESide {
	ePlayer,
	eEnemy,
	eNeutral
};

class Visulization;

class Entity
{
private:
	//positions
	Vector2 m_position;
	Vector2 m_oldPosition;
protected:

	//sprite data
	std::string m_spriteName;
	bool m_alive{ true };
	float m_speed{ 20.0f };

	//For bullets
	bool firebullet{ false };
	bool m_isBullet{ false };

	//frames
	int m_frameNum{ 0 };
	int m_numFrame{ 0 }; 

	//damage and health
	int m_DamageInflict{ 1 };
	int Health{ 0 };
	int m_Eside{ 1 };
	int m_bullets{ 0 };

	//ticks for constant animation 
	DWORD m_lastTimeUpdatedAnimation{ 0 };
	DWORD m_animationTime{ 50 };
public:
	//constructors
	Entity(std::string spriteName);
	virtual ~Entity();

	//functions to do complex tasks like checking collision
	void SetPosition(Vector2 newPos) { m_oldPosition = m_position; m_position = newPos; }
	void Render(Visulization&viz, float s);
	void CheckCollision(Visulization& Viz, Entity& other);
	
	//simple functions to return values needed elsewhere
	Vector2 GetPosition() const { return m_position; }
	bool isAlive() const { return m_alive; }
	bool Firebullet() const { return firebullet; }
	bool isBullet() const { return m_isBullet; }
	int EsideNumber() const { return m_Eside; }
	bool canFire();

	//makes the entity alive and set values to variables in entity
	void alive() { m_alive = true; Health = 3; };
	
	void TakeDamage(int dmg) { Health = Health - dmg; };

	//virtual
	virtual void Update() = 0;
	virtual ESide GetSide() const = 0;
};

