#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "stdafx.h"
#include "../Utility/DrawBatch.hpp"

namespace Mad
{
	namespace Manager
	{
		class Graphics
		{
		public:
			void createWindow(const std::string& title, int w, int h);

			sf::RenderTarget& getRenderTarget();
			sf::RenderWindow& getRenderWindow();
			float getAspectRatio() const;

			sf::View& getGameView();
			sf::View& getDefaultView();

			Utility::DrawBatch& getDrawBatch();

			// call before rendering the game world
			void beginGameRendering();
			void endGameRendering();

			// call between rendering things like UI
			void beginRendering();
			void endRendering();

			static Graphics* getSingleton();
			static Graphics* initialise();
			static void deinitialise();

		private:
			sf::RenderWindow m_Window;
			sf::View m_GameView, m_DefView;
			bool m_InsideBeginEnd;
//			Utility::DrawBatch m_DrawBatch;

			static Graphics* ms_Singleton;

			Graphics();
			Graphics(const Graphics&);
			~Graphics();
		};
	}
}

#endif /* _GRAPHICS_HPP_ */
