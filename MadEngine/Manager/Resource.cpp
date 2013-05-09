#include "stdafx.h"
#include "Resource.hpp"

Mad::Manager::Resource::Resource()
{
	m_Properties["TexturePath"] = "Assets/Texture/";
	m_Properties["TextureType"]	= "default";
	m_Properties["SFXPath"]		= "Assets/SFX/";
	m_Properties["AudioPath"]	= "Assets/Audio/";
}

Mad::Manager::Resource::~Resource()
{
}

void Mad::Manager::Resource::setSmoothTexture(bool flag)
{
	if (flag)
		m_Properties["TextureType"]	= "smooth";
}
std::string &Mad::Manager::Resource::getProperties(const std::string& name)
{
	auto it		= m_Properties.find(name);
	if (it != m_Properties.end())
		return it->second;

	std::cout<<"ERROR : "<<name<<" not reconigzed by system !"<<std::endl;
}

Mad::Manager::Resource *Mad::Manager::Resource::getSingleton()
{
	if (instance == nullptr)	
		instance	= new Resource();

	return instance;
}

void Mad::Manager::Resource::setProperties(const std::string &name, const std::string &value)
{
	//asdasd
}

void Mad::Manager::Resource::loadXMLData(const std::string& filepath)
{
	//load xml data
}

void Mad::Manager::Resource::loadTextureFromFile(const std::string& newTextureId, const std::string& fileName)
{
	std::string path	= getProperties("TexturePath");

	sf::Texture *t		= new sf::Texture;
	if (!t->loadFromFile(path+fileName))
		throw Mad::Manager::Exceptions::FileNotFound();

	if (m_Properties["TextureType"] == "smooth")
		t->setSmooth(true);

	m_TextureDB.insert(std::pair<std::string, sf::Texture*>(newTextureId, t));
}

void Mad::Manager::Resource::loadAudioFromFile(const std::string& newAudioId, const std::string& fileName)
{
	//load Audio
}

void Mad::Manager::Resource::loadSoundBufferFromFile(const std::string& newBufferId, const std::string& fileName)
{
	std::string path	= getProperties("SFXPath");

	sf::SoundBuffer * b	= new sf::SoundBuffer();
	if (!b->loadFromFile(path+fileName))
		throw Mad::Manager::Exceptions::FileNotFound();

	m_SoundBufferDB.insert(std::pair<std::string, sf::SoundBuffer*>(newBufferId, b));
}

sf::Texture *Mad::Manager::Resource::getTexture(const std::string& textureId)
{
	auto it		= m_TextureDB.find(textureId);
	if (it != m_TextureDB.end())
		return it->second;
	else
		Mad::Manager::Exceptions::ResourceNotFound();
	return 0;
}

sf::SoundBuffer *Mad::Manager::Resource::getSoundBuffer(const std::string& bufferId)
{
	auto it		= m_SoundBufferDB.find(bufferId);
	if (it != m_SoundBufferDB.end())
		return it->second;
	else
		Mad::Manager::Exceptions::ResourceNotFound();
	return 0;
}

Mad::Manager::Resource					*Mad::Manager::Resource::instance			= nullptr;
std::map<std::string, std::string>		Mad::Manager::Resource::m_Properties;
std::map<std::string, sf::Texture*>		Mad::Manager::Resource::m_TextureDB;
std::map<std::string, sf::Music*>		Mad::Manager::Resource::m_AudioDB;
std::map<std::string, sf::SoundBuffer*>	Mad::Manager::Resource::m_SoundBufferDB;
