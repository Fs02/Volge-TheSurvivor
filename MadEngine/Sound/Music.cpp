#include "Music.hpp"

Mad::Sound::Music::Music()
{
}

Mad::Sound::Music::Music(const std::string& file)
{
	loadFromFile(file);
}

Mad::Sound::Music::~Music()
{
}

void Mad::Sound::Music::loadFromFile(const std::string& file)
{
	if (!m_Data.openFromFile(file))
		throw Mad::Manager::Exceptions::FileNotFound();
}


sf::Music& Mad::Sound::Music::getMusic()
{
	return m_Data;
}