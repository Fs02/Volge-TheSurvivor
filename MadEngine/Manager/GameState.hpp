#ifndef _GAMESTATE_HPP_
#define _GAMESTATE_HPP_

namespace Mad
{
	namespace Manager
	{
		class GameState
		{
		public:
			static GameState* initialise();
			static void deinitialise();
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

#endif