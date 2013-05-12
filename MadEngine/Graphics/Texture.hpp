//
// Wrapper class for sf::Texture
//

#pragma once
#include "../../stdafx.h"
#include "../Interface/IResource.hpp"
#include "../Manager/Exceptions.hpp"

namespace Mad
{
	namespace Graphics
	{
		class Texture
			: public Mad::Interface::IResource
		{
		private:
			sf::Texture m_Data;
			sf::Vector2u m_Size;

		public:
			Texture();
			Texture(const std::string& file, sf::IntRect area = sf::IntRect());
			Texture(sf::Texture& sfTexture);
			~Texture();
			
			void loadFromFile(const std::string& file, sf::IntRect area = sf::IntRect());
			void loadFromSFTexture(sf::Texture& sfTexture);

			void setSmooth(bool flag);
			void setRepeated(bool flag);

			sf::Vector2u& getSize();
			sf::Texture& getTexture();
		};
	}
}