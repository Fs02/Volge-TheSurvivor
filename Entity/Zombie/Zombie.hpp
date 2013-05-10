#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../IEntity.hpp"
#include "../../CEntity/CSkeleton/Human.hpp"
#include "../../CEntity/CHealth/CHealth.hpp"
#include "../../CEntity/CAI/AIZombie.hpp"
#include "../../CEntity/CGraphics/CGZombie.hpp"

namespace Entity
{
	class Zombie:
		public virtual Entity::IEntity,
		public virtual CEntity::CSkeleton::Human,
		public virtual CEntity::CHealth,
		public virtual CEntity::CAI::AIZombie,
		public virtual CEntity::CGraphics::CGZombie
	{
	private:
		Mad::Graphics::AniSprite m_AniSprite;
		//male gun

	public:
		Zombie(PhysicsSystem* physicsInstance);
		~Zombie();

		void update(float deltaTime);
		void onCollisionBegin(Entity::IEntity* other);
		void onCollisionEnd(Entity::IEntity* other);
		void onDamage(Entity::IEntity* other, int damage);
	};
}
