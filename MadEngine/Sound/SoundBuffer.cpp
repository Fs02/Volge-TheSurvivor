#include "stdafx.h"
#include "SoundBuffer.hpp"

Mad::Sound::SoundBuffer::SoundBuffer()
{
}

Mad::Sound::SoundBuffer::SoundBuffer(const std::string& file)
{
	loadFromFile(file);
}

Mad::Sound::SoundBuffer::SoundBuffer(sf::SoundBuffer& data)
{
	loadFromSFBuffer(data);
}

Mad::Sound::SoundBuffer::~SoundBuffer()
{
}

void Mad::Sound::SoundBuffer::loadFromFile(const std::string& file)
{
	if (!m_Data.loadFromFile(file))
		throw Mad::Manager::Exceptions::FileNotFound();
}

void Mad::Sound::SoundBuffer::loadFromSFBuffer(sf::SoundBuffer& data)
{
	m_Data				= data;
}

sf::SoundBuffer& Mad::Sound::SoundBuffer::getBuffer()
{
	return m_Data;
}