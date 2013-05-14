#pragma once

#include "../../stdafx.h"
#include "Exceptions.hpp"
#include "../Interface/IResource.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Sprite.hpp"
#include "../Sound/SoundBuffer.hpp"
#include "../Sound/Music.hpp"

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
			static std::map<std::string, Mad::Interface::IResource*> m_ResourceDB;

			static std::string getProperties(const std::string& propertyId);

		public:
			static Resource* initialise();
			static void deinitialise();

			static Resource* getSingleton();

			static void setProperties(const std::string &name, const std::string &value);
			static void loadXMLData(const std::string& filepath);
			
			template<class T>
			static inline void load(const std::string& fileName);
			template<class T>
			static inline T* get(const std::string& fileName);
		};
	}
}


/*
 implementation
 */

template<class T>
inline void Mad::Manager::Resource::load(const std::string& fileName)
{
	// check if a resource already exists
	if(m_ResourceDB.count(fileName))
		return;

	std::string path;
	Mad::Interface::IResource* res;
	
	if (typeid(T) == typeid(Mad::Graphics::Texture))
	{
		path		= getProperties("TexturePath");
		Mad::Graphics::Texture* mT	= new Mad::Graphics::Texture(path+fileName);
		res			= mT;
	}
	else if(typeid(T) == typeid(Mad::Graphics::SpriteData))
	{
		path		= getProperties("SpritePath");
		Mad::Graphics::SpriteData* sd=new Mad::Graphics::SpriteData();
		sd->loadFromJSON(path+fileName);
		res			=sd;
	}
	else if(typeid(T) == typeid(Mad::Sound::SoundBuffer))
	{
		path		= getProperties("SFXPath");
		Mad::Sound::SoundBuffer* sB	= new Mad::Sound::SoundBuffer(path+fileName);
		res			= sB;
	}
	else if(typeid(T) == typeid(Mad::Sound::Music))
	{
		path		= getProperties("AudioPath");
		Mad::Sound::Music* mM		= new Mad::Sound::Music(path+fileName);
		res			= mM;
	}
	else
	{
		throw Mad::Manager::Exceptions::Error("Invalid Resource Type !");
	}
	m_ResourceDB.insert(std::pair<std::string, Mad::Interface::IResource*>(fileName,res));
}

template<class T>
inline T* Mad::Manager::Resource::get(const std::string& fileName)
{
	if (m_ResourceDB.find(fileName) == m_ResourceDB.end())
		Mad::Manager::Exceptions::InvalidKey("Resource index!");

	return dynamic_cast<T*>(m_ResourceDB[fileName]);
}
