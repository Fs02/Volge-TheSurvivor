#include "stdafx.h"
#include "SoundComponent.hpp"

SoundComponent::SoundComponent()
{
}

SoundComponent::~SoundComponent()
{
	for (auto it = m_SFXList.begin(); it != m_SFXList.end();)
	{
		delete it->second;
		it = m_SFXList.erase(it);
	}
}

std::string SoundComponent::getTypeName() const
{
	return "Sound";
}

std::list<Property> SoundComponent::listProperties() const
{
	// TODO
	return std::list<Property>();
}

void SoundComponent::addSound(const std::string& eventName, const std::string& soundId, bool repeatPlay)
{
	Mad::Sound::SoundBuffer* sb	= Mad::Manager::Resource::get<Mad::Sound::SoundBuffer>(soundId);
	sf::Sound* sound			= new sf::Sound();
	sound->setBuffer(sb->getBuffer());
	sound->setLoop(repeatPlay);
	m_SFXList[eventName]	= sound;
}

void SoundComponent::initialise(Entity* owner)
{
}

void SoundComponent::update(float deltaTime)
{
}

void SoundComponent::onGenericEvent(const std::string& name)
{
	m_SFXList[name]->play();
}

