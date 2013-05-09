#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../IEntity.hpp"
#include "../../CEntity/EnumStates.hpp"
#include "../../CEntity/CSkeleton/Human.hpp"
#include "../../CEntity/CAI/Player.hpp"
#include "../../CEntity/CWeapon/CGun.hpp"
#include "../../CEntity/CHealth/CHealth.hpp"

namespace Entity
{
	class Soldier: 
		public virtual Entity::IEntity,
		public virtual CEntity::CSkeleton::Human,
		public virtual CEntity::CAI::Player,
		public virtual CEntity::CHealth
	{
	private:
		Mad::Manager::Controller* m_Controller;
		Mad::Graphics::AniSprite m_AniSprite;
		CEntity::CWeapon::CGun* m_Waepon;

		sf::Sound m_FootSteps;
		b2World* m_World;

	public:
		Soldier(b2World* World);
		~Soldier();

		void update();
		void draw();
	};
}
