#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "../Manager/GameState.hpp"
#include "../Manager/Resource.hpp"
#include "../Manager/Controller.hpp"
#include "../Manager/Graphics.hpp"
#include "../3rdParty/FrameClock/FrameClock.hpp"
#include "../3rdParty/FrameClock/ClockHUD.hpp"
#include "../3rdParty/b2DebugDraw/DebugDraw.hpp"
#include "../Graphics/Sprite.hpp"

namespace Mad
{
	namespace Interface
	{
		class IGame
		{
		protected:
			sf::View m_Camera;
			sf::Event m_Event;
			sfx::FrameClock frameStats;
			bool isQuit;
			bool isDisplayFrameStats;

			IGame();
			virtual ~IGame();

			Mad::Manager::GameState *GameState;
			Mad::Manager::Resource *ResourceProvider;
			Mad::Manager::Controller *Controller;
			Mad::Manager::Graphics *Graphics;

			void setDisplayStatistics(bool flag);
			void quit();
			void cleanUp();

			void b2DebugDraw(b2World* world);

		public:
			void start();

			virtual void initialize();
			virtual void load();
			virtual void update();
			virtual void unLoad();
		};
	}
}
