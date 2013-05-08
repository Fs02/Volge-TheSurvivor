#pragma once

#include "..\..\stdafx.h"
#include "Exceptions.hpp"

namespace Mad
{
	namespace Manager
	{
		class Resource
		{
		private:
			Resource();
			~Resource();

			static Resource* instance;

			static std::map<std::string, std::string>		m_Properties;
			static std::map<std::string, sf::Texture*>		m_TextureDB;
			static std::map<std::string, sf::Music*>		m_AudioDB;
			static std::map<std::string, sf::SoundBuffer*>	m_SoundBufferDB;

			static std::string& getProperties(const std::string& propertyId);

		public:
			static Resource* getSingleton();

			static void setProperties(const std::string &name, const std::string &value);
			static void setSmoothTexture(bool flag = true);

			static void loadXMLData(const std::string& filepath);
			static void loadTextureFromFile(const std::string& newTextureId, const std::string& fileName);
			static void loadAudioFromFile(const std::string& newAudioId, const std::string& fileName);
			static void loadSoundBufferFromFile(const std::string& newBufferId, const std::string& fileName);

			static sf::Texture *getTexture(const std::string& textureId);
			static sf::SoundBuffer *getSoundBuffer(const std::string& bufferId);
		};
	}
}