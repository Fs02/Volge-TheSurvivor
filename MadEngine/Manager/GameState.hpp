#pragma once

#include "../../stdafx.h"

namespace Mad
{
	namespace Manager
	{
		class GameState
		{
		public:
			static GameState *getSingleton();
			static int getCurrentState();
			static void changeState(int state);

		private:
			GameState();
			~GameState();

			static GameState *instance;
			static int m_States;
		};
	}
}
