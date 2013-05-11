//
// wrapper for sf::Music
//

#pragma once
#include "../../stdafx.h"
#include "../Interface/IResource.hpp"
#include "../Manager/Exceptions.hpp"

namespace Mad
{
	namespace Sound
	{
		class Music
			: public Mad::Interface::IResource
		{
		private:
			sf::Music m_Data;

		public:
			Music();
			Music(const std::string& file);
			~Music();

			void loadFromFile(const std::string& file);

			sf::Music& getMusic();
		};
	}
}