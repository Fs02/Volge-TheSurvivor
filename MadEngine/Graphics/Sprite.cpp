#include "stdafx.h"
#include "Sprite.hpp"
#include "../Utility/DrawBatch.hpp"

/*
 * Mad::Graphics::Animation
 */

Mad::Graphics::Animation::Animation(SpriteData& data)
		: m_Data(data), m_Length(1)
{
}

void Mad::Graphics::Animation::setLength(float time)
{
	m_Length = time;
}

void Mad::Graphics::Animation::addFrame(int index)
{
	m_Frames.push_back(m_Data.getFrameArea(index));
}

void Mad::Graphics::Animation::draw(sf::Sprite& sp, const b2Vec2& size, float time, bool looped) const
{
	if(m_Length <= 0)
		return;

	if(time < 0)
		time=0;

	while(looped && time > m_Length)
		time-=m_Length;
	if(!looped && time > m_Length)
		time=m_Length;

	int frame=(int)std::round((float)(m_Frames.size()-1)*time/m_Length);
	sp.setTexture(*m_Data.getTexture());
	sp.setTextureRect(m_Frames[frame]);
}

/*
 * Mad::Graphics::SpriteData
 */

Mad::Graphics::SpriteData::SpriteData()
		: m_Texture(nullptr)
{
}

Mad::Graphics::SpriteData::~SpriteData()
{
	this->unload();
}

void Mad::Graphics::SpriteData::setTexture(sf::Texture* tex)
{
	delete m_Texture;
	m_Texture = tex;
}

void Mad::Graphics::SpriteData::divideIntoFrames(int frameW, int frameH)
{
	int nHor = m_Texture->getSize().x / frameW;
	int nVer = m_Texture->getSize().y / frameH;

	int x = 0, y = 0;
	for (int i = 0; i < nHor; ++i)
	{
		for (int j = 0; j < nVer; ++j)
		{
			sf::Rect<int> fr;
			fr.left = x;
			fr.top = y;
			fr.width = frameW;
			fr.height = frameH;
			m_Frames.push_back(fr);
		}

		x += frameW;
		y = 0;
	}
}

void Mad::Graphics::SpriteData::unload()
{
	delete m_Texture;
	m_Texture = nullptr;
	for (auto iter = m_Animations.begin(); iter != m_Animations.end(); ++iter)
		delete iter->second;
	m_Animations.clear();
	m_Frames.clear();
}

sf::Texture* Mad::Graphics::SpriteData::getTexture()
{
	return m_Texture;
}

Mad::Graphics::Animation* Mad::Graphics::SpriteData::getAnimation(
		const std::string& name)
{
	auto iter = m_Animations.find(name);
	if (iter == m_Animations.end())
		return nullptr;
	return iter->second;
}

const Mad::Graphics::Animation* Mad::Graphics::SpriteData::getAnimation(
		const std::string& name) const
{
	auto iter = m_Animations.find(name);
	if (iter == m_Animations.end())
		return nullptr;
	return iter->second;
}

sf::Rect<int> Mad::Graphics::SpriteData::getFrameArea(int frameIndex) const
{
	if (frameIndex < 0 || frameIndex >= (int) m_Frames.size())
		return sf::Rect<int>();
	return m_Frames[frameIndex];
}

/*
 * Mad::Graphics::Sprite
 */

Mad::Graphics::Sprite::Sprite()
	:m_Data(nullptr), m_Anim(nullptr), m_Looped(true), m_Time(0)
{
}

Mad::Graphics::Sprite::Sprite(const std::string& spriteDataName)
		: m_Data(nullptr), m_Anim(nullptr), m_Looped(true), m_Time(0)
{
	// TODO
}

Mad::Graphics::Sprite::Sprite(const SpriteData* sd)
		: m_Data(sd), m_Anim(nullptr), m_Looped(true), m_Time(0)
{
}

void Mad::Graphics::Sprite::setSource(const std::string& spriteDataName)
{
	// TODO
}

void Mad::Graphics::Sprite::setAnimation(const std::string& name)
{
	m_Anim = m_Data->getAnimation(name);
}

void Mad::Graphics::Sprite::setLooped(bool looped)
{
	m_Looped = looped;
}

void Mad::Graphics::Sprite::setTime(float time)
{
	m_Time = time;
}

float Mad::Graphics::Sprite::getTime() const
{
	return m_Time;
}

const Mad::Graphics::Animation* Mad::Graphics::Sprite::getAnimation() const
{
	return m_Anim;
}

void Mad::Graphics::Sprite::setPosition(const b2Vec2& pos)
{
	m_Sprite.setPosition(pos.x, pos.y);
}

b2Vec2 Mad::Graphics::Sprite::getPosition() const
{
	sf::Vector2f pos=m_Sprite.getPosition();
	return b2Vec2(pos.x, pos.y);
}

void Mad::Graphics::Sprite::setOrigin(const b2Vec2& org)
{
	m_Sprite.setOrigin(org.x, org.y);
}

b2Vec2 Mad::Graphics::Sprite::getOrigin() const
{
	sf::Vector2f org=m_Sprite.getOrigin();
	return b2Vec2(org.x, org.y);
}

void Mad::Graphics::Sprite::setSize(const b2Vec2& size)
{
	m_Size=size;
}

const b2Vec2& Mad::Graphics::Sprite::getSize() const
{
	return m_Size;
}

void Mad::Graphics::Sprite::setRotation(float rot)
{
	m_Sprite.setRotation(rot*180.0f/b2_pi);
}

float Mad::Graphics::Sprite::getRotation() const
{
	return m_Sprite.getRotation()*b2_pi/180.0f;
}

void Mad::Graphics::Sprite::draw(float dt)
{
	if (m_Anim)
		m_Anim->draw(m_Sprite, m_Size, m_Time, m_Looped);
	m_Time += dt;
}
