#include "Sprite.hpp"

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

void Mad::Graphics::Animation::draw(sf::RenderTarget& rt, const b2Vec2& pos,
		const b2Vec2& org, const b2Vec2& size, float time, bool looped) const
{
	if (time > m_Length)
	{
		while (looped && time > m_Length)
			time -= m_Length;

		if (!looped)
			time = m_Length;
	}

	int index = (int) std::round(((float) m_Frames.size()) * time / m_Length);

	sf::Texture& tex = *m_Data.getTexture();
	sf::Sprite sprt;
	sprt.setTexture(tex);
	sprt.setTextureRect(m_Frames[index]);
	sprt.setPosition(pos.x, pos.y);
	sprt.setOrigin(org.x, org.y);
	sprt.setScale((float) tex.getSize().x / size.x,
			(float) tex.getSize().y / size.y);
	rt.draw(sprt);
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

Mad::Graphics::Sprite::Sprite(const std::string& spriteDataName)
		: m_Data(nullptr), m_Anim(nullptr), m_Looped(true), m_Time(0), m_Pos(0,
				0), m_Origin(0, 0), m_Size(0, 0)
{
}

Mad::Graphics::Sprite::Sprite(const SpriteData* sd)
		: m_Data(sd), m_Anim(nullptr), m_Looped(true), m_Time(0), m_Pos(0, 0), m_Origin(
				0, 0), m_Size(0, 0)
{
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
	m_Pos = pos;
}

const b2Vec2& Mad::Graphics::Sprite::getPosition() const
{
	return m_Pos;
}

void Mad::Graphics::Sprite::setOrigin(const b2Vec2& org)
{
	m_Origin = org;
}

const b2Vec2& Mad::Graphics::Sprite::getOrigin() const
{
	return m_Origin;
}

void Mad::Graphics::Sprite::setSize(const b2Vec2& size)
{
	m_Size = size;
}

const b2Vec2& Mad::Graphics::Sprite::getSize() const
{
	return m_Size;
}

void Mad::Graphics::Sprite::draw(sf::RenderTarget& rt, float dt)
{
	if (m_Anim)
		m_Anim->draw(rt, m_Pos, m_Origin, m_Size, m_Time, m_Looped);
	m_Time += dt;
}
