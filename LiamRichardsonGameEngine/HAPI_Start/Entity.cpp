#include "Entity.h"
#include "Visulization.h"


Entity::Entity(std::string spriteName) : m_spriteName(spriteName)
{
}

Entity::~Entity()
{
}

void Entity::Render(Visulization& viz, float s)
{
	//if not alive dont do anything
	if (!m_alive)
		return;
	
	//calculated imbetween of old position and new position for smooth movement
	Vector2 interposition{ m_oldPosition + (m_position - m_oldPosition) * s };
	
	//render function in vizulation
	viz.Render(m_spriteName, (int)interposition.x, (int)interposition.y, m_frameNum); 

	//repeating animation since only on enemy enties made it trigger for them only
	if (m_spriteName == "Enemy" && m_alive == true) 
		if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime) {
			m_frameNum++;
			if (m_frameNum >= m_numFrame)
				m_frameNum = 1;

			m_lastTimeUpdatedAnimation = HAPI.GetTime();
		}

}

void Entity::CheckCollision(Visulization& Viz, Entity& other)
{
	//if not alive dont do anything
	if (!m_alive)
		return;

	//check if same side if so no point in continuing
	if (GetSide() == other.GetSide())
		return;

	//check if neutal side if so no point doing rest of code
	else if (other.GetSide() == ESide::eNeutral)
		return;

	//cehck to see if the entity being checked against is alive otherwise no point
	if (!other.m_alive)
		return;

	//create replicate rectangle of the target entity (e.g the player)
	Rectangle thisRect{ Viz.getRect(m_spriteName,1), Viz.getRect(m_spriteName,2), Viz.getRect(m_spriteName,3), Viz.getRect(m_spriteName,4) };

	int w{ thisRect.width() };


	thisRect.left += w / 10;
	thisRect.right += w / 10;

	
	//create replicate rectangle of target entity to compare the two
	Rectangle otherRect{ Viz.getRect(other.m_spriteName,1), Viz.getRect(other.m_spriteName,2), Viz.getRect(other.m_spriteName,3), Viz.getRect(other.m_spriteName,4) };

	//translate positons
	thisRect.Translate((int)m_position.x, (int)m_position.y);
	otherRect.Translate((int)other.m_position.x, (int)other.m_position.y);

	//check if collision
	if (!thisRect.CompletlyOutside(otherRect)) {
		//collision occured
		TakeDamage(other.m_DamageInflict);
		other.TakeDamage(m_DamageInflict);
		
	}

}

bool Entity::canFire()
{
	//CHANGE
	if (m_bullets >= 1)
		return false;

	m_bullets++;
	return true;
	
}

