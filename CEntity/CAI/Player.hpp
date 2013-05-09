#pragma once

#include "../../stdafx.h"
#include "../ICEntity.hpp"
#include "../CWeapon/CGun.hpp"
#include "../../MadEngine/MadEngine.hpp"

namespace CEntity
{
	namespace CAI
	{
		class Player
			: public CEntity::ICEntity
		{
		public:
			Player(PhysicsSystem* physicsInstance);
			~Player();

			int getAIState();
			void setAIState(int state);
			void unsetAIState(int state);

		protected:
			void update(float deltaTime);
			void onCollisionBegin(Entity::IEntity* other);
			void onCollisionEnd(Entity::IEntity* other);
			
		private:
			int m_State;
			int m_prevState;
			Mad::Manager::Controller* m_Controller;
			float m_TotalTime;
			
			void resetState();
		};
	}
}
