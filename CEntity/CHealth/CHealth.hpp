#pragma once

#include "../../stdafx.h"
#include "../ICEntity.hpp"

namespace CEntity
{
	class CHealth
		: public CEntity::ICEntity
	{
	private:
		int m_Health;
		const int m_MaxHealth;

	protected:
		CHealth(PhysicsSystem* physicsIntance ,int Health);
		~CHealth();
	
		void update(float deltaTime);
//		void onCollisionBegin(Entity::IEntity* other);
//		void onCollisionEnd(Entity::IEntity* other);
		void onDamage(Entity::IEntity* other, int damage);

	public:
		void increaseHealthPoints(int points = 1);
		void decreaseHealthPoints(int points = 1);
		int getHealthPoints();
	};
}
