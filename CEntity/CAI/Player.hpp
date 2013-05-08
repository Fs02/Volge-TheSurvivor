#pragma once

#include "..\..\..\stdafx.h"
#include "..\CWaepon\CGun.hpp"
#include "..\..\MadEngine\MadEngine.hpp"
#include "..\EnumStates.hpp"

namespace CEntity
{
	namespace CAI
	{
		class Player
		{
		public:
			Player();
			~Player();

			int getAIState();
			void setAIState(int state);
			void unsetAIState(int state);

			void updateAI();
			
		private:
			int m_State;
			int m_prevState;
			sf::Clock m_Clock;
			Mad::Manager::Controller* m_Controller;
			float m_Time;
			
			void resetState();
		};
	}
}