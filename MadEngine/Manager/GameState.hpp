#pragma once

#include "..\..\stdafx.h"

namespace Mad
{
	namespace Manager
	{
		class GameState
		{
		public:
			enum States{Uninitialized, Splash, Pause, Resume, Menu, Load, Play, Exit};
			static GameState *getSingleton();
			static States getCurrentState();
			static void changeState(States state);

		private:
			GameState();
			~GameState();

			static GameState *instance;
			static States m_States;
		};
	}
}