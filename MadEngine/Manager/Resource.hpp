#pragma once

#include "../../stdafx.h"
#include "Exceptions.hpp"
#include "../Interface/IResource.hpp"
#include "../Graphics/Texture.hpp"
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

			static std::string& getProperties(const std::string& propertyId);

		public:
			static Resource* getSingleton();

			static void setProperties(const std::string &name, const std::string &value);
			static void loadXMLData(const std::string& filepath);
			
			template<class T>
			static inline void load(const std::string& id, const std::string& fileName);
			template<class T>
			static inline T* get(const std::string& id);
		};
	}
}


/*
 implementation
 */

template<class T>
inline void Mad::Manager::Resource::load(const std::string& id, const std::string& fileName)
{
	std::string path;
	Mad::Interface::IResource* res;
	
	if (typeid(T) == typeid(Mad::Graphics::Texture))
	{
		path		= getProperties("TexturePath");
		Mad::Graphics::Texture* mT	= new Mad::Graphics::Texture(path+fileName);
		res			= mT;
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
	m_ResourceDB.insert(std::pair<std::string, Mad::Interface::IResource*>(id,res));
}

template<class T>
inline T* Mad::Manager::Resource::get(const std::string& id)
{
	if (m_ResourceDB.find(id) == m_ResourceDB.end())
		Mad::Manager::Exceptions::InvalidKey("Resource index!");

	return dynamic_cast<T*>(m_ResourceDB[id]);
}