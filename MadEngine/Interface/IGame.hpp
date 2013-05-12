#pragma once

#include "../../stdafx.h"
#include "../Manager/GameState.hpp"
#include "../Manager/Resource.hpp"
#include "../Manager/Controller.hpp"
#include "../Utility/DrawBatch.hpp"
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
			sf::RenderWindow m_Window;
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
			Mad::Utility::DrawBatch *DrawBatch;

			void create(unsigned int windowWidth, unsigned int windowHeight, unsigned int BitsPerPixel, const std::string& title, bool fullScreen = false);
			void setFrameLimit(unsigned int limit);
			void setVerticalSyncEnabled(bool flag);
			void setMouseCursorVisible(bool flag);
			void setDisplayStatistics(bool flag);
			void setUseSmoothTexture(bool flag);
			void quit();
			void cleanUp();

			sf::RenderWindow* getSFWindow();

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
