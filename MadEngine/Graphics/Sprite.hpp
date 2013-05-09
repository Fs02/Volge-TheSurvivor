#pragma once

#include "../../stdafx.h"
#include "../Utility/DrawBatch.hpp"

namespace Mad
{
	namespace Graphics
	{
		class Sprite
		{
		protected:
			std::string m_TextureId;

			sf::Vector2f m_Position;
			float m_Angle;
			sf::Vector2f m_Origin;
			sf::Vector2f m_Size;
			sf::IntRect m_Rect;
			
			Mad::Utility::DrawBatch *DrawBatch;

			sf::Texture& getTexture();

		public:
			Sprite();
			Sprite(const std::string& textureId);
			Sprite(const std::string& textureId, const sf::IntRect& rectArea);
			~Sprite();

			void draw();

			void setTexture(const std::string& textureId);
			void setTextureRect(const sf::IntRect& rectArea);
			void setPosition(float x, float y);
			void setPosition(const sf::Vector2f& Position);
			void setRotation(float angle);
			void setOrigin(float x, float y);
			void setOrigin(const sf::Vector2f& Origin);

			sf::Vector2f& getPosition();
			float getRotation();
			sf::Vector2f& getOrigin();
			sf::Vector2f& getSize();
			std::string& getTextureId();
		};
	}
}
