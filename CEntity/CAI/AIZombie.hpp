#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../EnumStates.hpp"

namespace CEntity
{
	namespace CAI
	{
		class AIZombie
		{
		public:
			AIZombie();
			~AIZombie();

			int getAIState();
			void setAIState(int state);
			void unsetAIState(int state);
			void addTarget(b2Body* body);
			void removeTarget(b2Body* body);

			void updateAI();

		protected:
			void setAIBody(b2Body* body);

		private:
			int m_State;
			int m_prevState;
			sf::Clock m_Clock;
			float m_Time;
			b2Body* m_Bodyptr;
			std::vector<b2Body*> m_TargetList;

			void resetState();
			b2Vec2 getNearestTarget();
		};
	}
}
