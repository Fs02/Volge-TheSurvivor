#pragma once 

#include "../stdafx.h"
#include "../MadEngine/MadEngine.hpp"
#include "../Entity/IEntity.hpp"

class PhysicsSystem;

//AI parts
namespace STATE
{
	enum {
			IDLE		= 1,
			STEADY		= 1 << 1,
			FORWARD		= 1 << 2,
			BACKWARD	= 1 << 3,
			LEFT		= 1 << 4,
			RIGHT		= 1 << 5,
			ATTACK		= 1 << 6,
			RELOAD		= 1 << 7, 
			THROW		= 1 << 8
	};
}

namespace CEntity
{
	//Skeleton Parts
	//Category Bits
	enum {
		UNDEFINED	= 1, 
		CIVILIAN	= 1 << 1,
		SOLDIER		= 1 << 2,
		ZOMBIE		= 1 << 3,
		CENSOR		= 1 << 4,	  
		BULLET		= 1 << 5
	};
	
	//Physics Component
	struct PhysicsComponent  {
		float32 previousAngle;
		float32 smoothedAngle;	
		b2Vec2 previousPosition;
		b2Vec2 smoothedPosition;
	};


	class ICEntity
	{
	protected:
		ICEntity(PhysicsSystem* instance);
		~ICEntity();

		virtual void update(float deltaTime) = 0;
		/* I've added implementations, so that
		 * we don't have to write dummy implementations
		 * for components not using these methods.
		 * These implementations do nothing.
		 */
		virtual void onCollisionBegin(Entity::IEntity* other);
		virtual void onCollisionEnd(Entity::IEntity* other);
		virtual void onDamage(Entity::IEntity* other, int damage);

		PhysicsSystem* m_PhysicsSystem;
	};
}
