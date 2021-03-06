#include "Resource.hpp"
#include <iostream>

Mad::Manager::Resource* Mad::Manager::Resource::initialise()
{
	return getSingleton();
}

void Mad::Manager::Resource::deinitialise()
{
	delete instance;
	instance	= nullptr;
}

Mad::Manager::Resource::Resource()
{
	m_Properties["TexturePath"] = "Assets/Texture/";
	m_Properties["SpritePath"]	= "Assets/Sprite/";
	m_Properties["SFXPath"]		= "Assets/SFX/";
	m_Properties["AudioPath"]	= "Assets/Audio/";
}

Mad::Manager::Resource::~Resource()
{
	for(auto iter=m_ResourceDB.begin(); iter != m_ResourceDB.end(); ++iter)
	{
		delete iter->second;
		iter = m_ResourceDB.erase(iter);
	}
}

std::string Mad::Manager::Resource::getProperties(const std::string& name)
{
	auto it		= m_Properties.find(name);
	if (it != m_Properties.end())
		return it->second;

	std::cout<<"ERROR : "<<name<<" not reconigzed by system !"<<std::endl;
	return std::string();	// to make Eclipse happy
}

Mad::Manager::Resource *Mad::Manager::Resource::getSingleton()
{
	if (instance == nullptr)	
		instance	= new Resource();

	return instance;
}

void Mad::Manager::Resource::setProperties(const std::string &name, const std::string &value)
{
	m_Properties[name]=value;
}

void Mad::Manager::Resource::loadXMLData(const std::string& filepath)
{
	//load xml data
}

Mad::Manager::Resource					*Mad::Manager::Resource::instance			= nullptr;
std::map<std::string, std::string>		Mad::Manager::Resource::m_Properties;
std::map<std::string, Mad::Interface::IResource*> Mad::Manager::Resource::m_ResourceDB;
