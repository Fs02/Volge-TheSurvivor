#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../ICEntity.hpp"

namespace CEntity
{
	namespace CAI
	{
		class AIZombie
			: public CEntity::ICEntity
		{
		public:
			AIZombie(PhysicsSystem* physicsInstance);
			~AIZombie();

			int getAIState();
			void setAIState(int state);
			void unsetAIState(int state);
			void addTarget(b2Body* body);
			void removeTarget(b2Body* body);

		protected:
			void update(float deltaTime);
			void onCollisionBegin(Entity::IEntity* other);
			void onCollisionEnd(Entity::IEntity* other);

			void setAIBody(b2Body* body);

		private:
			int m_State;
			int m_prevState;
			float m_TotalTime;
			b2Body* m_Bodyptr;
			std::vector<b2Body*> m_TargetList;

			void resetState();
			b2Vec2 getNearestTarget();
		};
	}
}
