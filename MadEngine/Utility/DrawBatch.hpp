#pragma once

#include "..\..\stdafx.h"
#include "..\Manager\Resource.hpp"

namespace Mad
{
	namespace Utility
	{
		class DrawBatch
		{
		private:
			DrawBatch();
			~DrawBatch();

			static DrawBatch* instance;
			static sf::RenderWindow* m_TargetWindow;
			static Mad::Manager::Resource *m_ResourceMan;

			static sf::Font *m_Font;
			static sf::Text *m_Text;
			static sf::Sprite *m_Sprite;
			static sf::RectangleShape *m_RectShape;
			static sf::CircleShape *m_CircleShape;

		public:
			static DrawBatch* getSingleton();
			static void setDrawTarget(sf::RenderWindow& targetWindow);

			static void begin();
			static void end();
			static void cleanUp();

			static void drawText(const std::string& text, sf::Vector2f& pos = sf::Vector2f(0,0), float rot = 0.f, int size =30, const sf::Color& color = sf::Color::Black, sf::Text::Style style = sf::Text::Regular);
			//primitive shape drawing
			
			static void drawSprite(const std::string& textureId, sf::Vector2f& pos, float rot = 0.f, sf::Vector2f& origin = sf::Vector2f(0,0));
			static void drawSprite(const std::string& textureId, sf::IntRect& area, sf::Vector2f& pos, float rot = 0.f, sf::Vector2f& origin = sf::Vector2f(0,0));
		};
	}
}