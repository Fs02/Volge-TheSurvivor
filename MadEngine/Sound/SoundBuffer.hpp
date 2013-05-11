//
// wrapper class for sf::soundbuffer
//

#pragma once
#include "../../stdafx.h"
#include "../Interface/IResource.hpp"
#include "../Manager/Exceptions.hpp"

namespace Mad
{
	namespace Sound
	{
		class SoundBuffer
			: public Mad::Interface::IResource
		{
		private:
			sf::SoundBuffer m_Data;

		public:
			SoundBuffer();
			SoundBuffer(const std::string& file);
			SoundBuffer(sf::SoundBuffer& data);
			~SoundBuffer();

			void loadFromFile(const std::string& file);
			void loadFromSFBuffer(sf::SoundBuffer& data);

			sf::SoundBuffer& getBuffer();
		};
	}
}