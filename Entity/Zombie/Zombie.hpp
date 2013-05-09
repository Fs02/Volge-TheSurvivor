#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../IEntity.hpp"
#include "../../CEntity/CSkeleton/Human.hpp"
#include "../../CEntity/CHealth/CHealth.hpp"
#include "../../CEntity/CAI/AIZombie.hpp"

namespace Entity
{
	class Zombie:
		public virtual Entity::IEntity,
		public virtual CEntity::CSkeleton::Human,
		public virtual CEntity::CHealth,
		public virtual CEntity::CAI::AIZombie
	{
	private:
		Mad::Graphics::AniSprite m_AniSprite;
		//male gun

		b2World* m_World;

	public:
		Zombie(PhysicsSystem* physicsInstance, b2World* World);
		~Zombie();

		void update(float deltaTime);
		void onCollisionBegin(Entity::IEntity* other);
		void onCollisionEnd(Entity::IEntity* other);
		void draw();
	};
}
