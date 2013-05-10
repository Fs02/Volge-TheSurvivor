#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../IEntity.hpp"
#include "../../CEntity/CSkeleton/Human.hpp"
#include "../../CEntity/CAI/Player.hpp"
#include "../../CEntity/CWeapon/CGun.hpp"
#include "../../CEntity/CHealth/CHealth.hpp"
#include "../../CEntity/CGraphics/CGSoldier.hpp"

namespace Entity
{
	class Soldier: 
		public virtual Entity::IEntity,
		public virtual CEntity::CSkeleton::Human,
		public virtual CEntity::CAI::Player,
		public virtual CEntity::CHealth,
		public virtual CEntity::CGraphics::CGSoldier
	{
	private:
		Mad::Manager::Controller* m_Controller;
		CEntity::CWeapon::CGun* m_Waepon;

		sf::Sound m_FootSteps;

	public:
		Soldier(PhysicsSystem* physicsInstance);
		~Soldier();

		void update(float deltaTime);
		void onCollisionBegin(Entity::IEntity* other);
		void onCollisionEnd(Entity::IEntity* other);
		void onDamage(Entity::IEntity* other, int damage);
	};
}
