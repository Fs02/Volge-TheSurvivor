#include "stdafx.h"
#include "AniSprite.hpp"

Mad::Graphics::AniSprite::AniSprite()
	: Mad::Graphics::Sprite()
{
	m_Fps			= 1;
	m_CurrentFrame	= 0;
	m_IsPlaying		= false;
	m_IsInvert		= false;
	m_LoopStart		= 0;
	setFrameSize(0,0);
}

Mad::Graphics::AniSprite::AniSprite(const std::string& textureId, int frameWidth, int frameHeight)
	: Mad::Graphics::Sprite(textureId)
{
	m_Fps			= 1;
	m_CurrentFrame	= 0;
	m_IsPlaying		= false;
	m_LoopStart		= 0;
	setFrameSize(frameWidth, frameHeight);
	setOrigin(frameWidth/2,frameHeight/2);
}

Mad::Graphics::AniSprite::~AniSprite()
{
}

sf::IntRect Mad::Graphics::AniSprite::getFrameRect(int frame)
{
	unsigned int across		= getTexture().getSize().x / m_FrameWidth;
	unsigned int down		= getTexture().getSize().y / m_FrameHeight;

	int tileY				= frame / across;
	int tileX				= frame % across;

	sf::IntRect result
		(tileX * m_FrameWidth,
		 tileY * m_FrameHeight,
		 m_FrameWidth,
		 m_FrameHeight);

	return result;
}
int Mad::Graphics::AniSprite::getFrameCount()
{
	unsigned int across		= getTexture().getSize().x / m_FrameWidth;
	unsigned int down		= getTexture().getSize().y / m_FrameHeight;

	return across * down;
}

int Mad::Graphics::AniSprite::getCurrentFrame()
{
	return m_CurrentFrame;
}

void Mad::Graphics::AniSprite::setFrameSize(int frameWidth, int frameHeight)
{
	m_FrameWidth		= frameWidth;
	m_FrameHeight		= frameHeight;
	setOrigin(frameWidth/2,frameHeight/2);
}

void Mad::Graphics::AniSprite::setCurrentFrame(int frame)
{
	m_CurrentFrame		= frame;
}

void Mad::Graphics::AniSprite::setLoopSpeed(int fps)
{
	m_Fps				= fps;
}

void Mad::Graphics::AniSprite::setInvertSprite(bool flag)
{
	m_IsInvert			= flag;
}

void Mad::Graphics::AniSprite::play()
{
	play(0, getFrameCount());
}

void Mad::Graphics::AniSprite::play(int start, int end)
{
	m_LoopStart			= start;
	m_LoopEnd			= end;
	m_IsPlaying			= true;
	m_CurrentFrame		= start;
	m_Clock.restart();
}

bool Mad::Graphics::AniSprite::isPlaying()
{
	return m_IsPlaying;
}

bool Mad::Graphics::AniSprite::isPlaying(int start, int end)
{
	if ((start == m_LoopStart) && (end == m_LoopEnd))
		return m_IsPlaying;
	
	return false;
}
void Mad::Graphics::AniSprite::stop()
{
	m_IsPlaying			= false;
}

void Mad::Graphics::AniSprite::update()
{
	if (m_IsInvert)
		m_Angle			+= 180;
	if (m_IsPlaying)
	{
		int frameCount		= (m_LoopEnd + 1) - m_LoopStart;

		float timePosition	= m_Clock.getElapsedTime().asSeconds() * m_Fps;

		m_CurrentFrame		= m_LoopStart + ((int)timePosition % frameCount);

		setTextureRect(getFrameRect(m_CurrentFrame));
	}
}