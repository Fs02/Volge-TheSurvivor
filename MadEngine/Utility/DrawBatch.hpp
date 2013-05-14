#ifndef _DRAWBATCH_HPP_
#define _DRAWBATCH_HPP_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "../Manager/Resource.hpp"

namespace Mad
{
	namespace Utility
	{
		class DrawBatch
		{
		private:
			 sf::RenderWindow* m_TargetWindow;

			 sf::Font *m_Font;
			 sf::Text *m_Text;
			 sf::Sprite *m_Sprite;
			 sf::RectangleShape *m_RectShape;
			 sf::CircleShape *m_CircleShape;

		public:
			DrawBatch();
			~DrawBatch();

			 void setDrawTarget(sf::RenderWindow& targetWindow);
			 sf::RenderTarget& getRenderTarget();

			 void begin();
			 void end();
			 void cleanUp();

			 void drawText(const std::string& text, const sf::Vector2f& pos = sf::Vector2f(0,0), float rot = 0.f, int size =30, const sf::Color& color = sf::Color::Black, sf::Text::Style style = sf::Text::Regular);
			//primitive shape drawing
			 void drawLine(const b2Vec2& a, const b2Vec2& b, const sf::Color& col);
			
			 void drawSprite(const sf::Sprite& sprite);
		};
	}
}

#endif