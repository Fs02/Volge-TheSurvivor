#include "stdafx.h"
#include "Sprite.hpp"
#include "../Manager/Resource.hpp"
#include "../Utility/DrawBatch.hpp"
#include "../3rdParty/JSON/JSON.hpp"
#include <fstream>
#include <iostream>

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
	if(m_Frames.size() == 0)
		return;

	if(time < 0)
		time=0;

	while(m_Length > 0 && looped && time > m_Length)
		time-=m_Length;
	if(!looped && time > m_Length)
		time=m_Length;

	int frame=0;
	if(m_Length > 0)
		frame=(int)std::round((float)(m_Frames.size()-1)*time/m_Length);

	float rw=sp.getTextureRect().width;
	float rh=sp.getTextureRect().height;

	if(size.x == 0 && size.y == 0)
		sp.setScale(1, 1);
	else
	{
		sf::Vector2f scale(size.x/rw, size.y/rh);
		sp.setScale(scale);
	}
	sp.setTexture(m_Data.getTexture()->getTexture());
	sp.setTextureRect(m_Frames[frame]);
	Utility::DrawBatch::drawSprite(sp);
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

void Mad::Graphics::SpriteData::setTexture(Texture* tex)
{
	m_Texture = tex;
}

void Mad::Graphics::SpriteData::divideIntoFrames(int frameW, int frameH)
{
	int tw=m_Texture->getSize().x;
	int th=m_Texture->getSize().y;
	frameW=std::min(frameW, tw);
	frameH=std::min(frameH, th);

	int nHor = tw / frameW;
	int nVer = th / frameH;

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

void Mad::Graphics::SpriteData::loadFromJSON(const std::string& name)
{
	json::Document doc;

	std::ifstream file(name.c_str());
	json::StdTokenStream tokenStr(file);
	json::StdErrorCallback errorCb(std::clog, name);

	if(!doc.load(&tokenStr, &errorCb))
		return;

	json::ValueHandle hRoot=doc.root();
	json::ValueHandle vh;

	vh=hRoot.childPair("Texture").value();
	std::string tex=vh.string();
	this->setTexture(Manager::Resource::get<Mad::Graphics::Texture>(tex));

	vh=hRoot.childPair("Texture division").value();
	{
		std::string tp=vh.childPair("Type").value().string();
		if(tp != "Matrix-column")
		{
			std::clog<<"Error while loading a sprite from "<<name<<": invalid texture division type!\n";
			return;
		}

		if(tp == "Matrix-column")
		{
			int w=vh.childPair("Width").value().integer(-1);
			int h=vh.childPair("Height").value().integer(-1);
			if(w <= 0 && h <= 0)
			{
				std::clog<<"Error while loading a sprite from "<<name<<": invalid frame size!\n";
				return;
			}
			this->divideIntoFrames(w, h);
		}
	}

	vh=hRoot.childPair("Animations").value();
	for(unsigned int anmIdx=0; anmIdx < vh.numChildren(); ++anmIdx)
	{
		json::ValueHandle hAnm=vh.childPair(anmIdx).value();
		Animation* anm=this->addAnimation(vh.childPair(anmIdx).name());

		double len=hAnm.childPair("Length").value().number(1);
		anm->setLength(len);

		json::ValueHandle hFrames=hAnm.childPair("Frames").value();
		for(unsigned int fi=0; fi < hFrames.numChildren(); ++fi)
		{
			int frame=hFrames.childValue(fi).integer(-1);
			if(frame < 0)
			{
				std::cout<<"Error while loading a sprite from "<<name<<": invalid frame index!\n";
				return;
			}
			anm->addFrame(fi);
		}
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

Mad::Graphics::Texture* Mad::Graphics::SpriteData::getTexture()
{
	return m_Texture;
}

Mad::Graphics::Animation* Mad::Graphics::SpriteData::addAnimation(const std::string& name)
{
	if(m_Animations.count(name))
		return nullptr;

	Animation* anm=new Animation(*this);
	m_Animations[name]=anm;
	return anm;
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
	:m_Data(nullptr), m_Anim(nullptr), m_Looped(true), m_Time(0), m_defOrigin(true), m_Size(1, 1)
{
}

Mad::Graphics::Sprite::Sprite(const std::string& spriteDataName)
		: m_Data(nullptr), m_Anim(nullptr), m_Looped(true), m_Time(0), m_defOrigin(true), m_Size(1, 1)
{
	m_Data=Manager::Resource::get<SpriteData>(spriteDataName);
	if(m_Data)
	{
		m_Anim=m_Data->getAnimation("Idle");
		this->setDefaultSize();
	}
}

Mad::Graphics::Sprite::Sprite(const SpriteData* sd)
		: m_Data(sd), m_Anim(nullptr), m_Looped(true), m_Time(0), m_defOrigin(true), m_Size(1, 1)
{
	m_Anim=m_Data->getAnimation("Idle");
	this->setDefaultSize();
}

void Mad::Graphics::Sprite::setSource(const std::string& spriteDataName)
{
	m_Data=Manager::Resource::get<SpriteData>(spriteDataName);
	m_Anim=m_Data->getAnimation("Idle");
	m_Looped=true;
	m_Time=0;
	m_Size.Set(0, 0);
	this->setDefaultSize();
}

void Mad::Graphics::Sprite::setSource(const SpriteData* sd)
{
	m_Data=sd;
	m_Anim=m_Data->getAnimation("Idle");
	m_Looped=true;
	m_Time=0;
	m_Size.Set(0, 0);
	this->setDefaultSize();
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
	m_defOrigin=false;
}

void Mad::Graphics::Sprite::setDefaultOrigin()
{
	m_defOrigin=true;
}

b2Vec2 Mad::Graphics::Sprite::getOrigin() const
{
	if(m_defOrigin)
		return 0.5f*this->getSize();
	sf::Vector2f org=m_Sprite.getOrigin();
	return b2Vec2(org.x, org.y);
}

void Mad::Graphics::Sprite::setSize(const b2Vec2& size)
{
	m_Size=size;
}

void Mad::Graphics::Sprite::setDefaultSize()
{
	m_Size.Set(0, 0);
}

b2Vec2 Mad::Graphics::Sprite::getSize() const
{
	if(m_Size.x == 0 && m_Size.y == 0)
		return b2Vec2(m_Sprite.getTextureRect().width, m_Sprite.getTextureRect().height);
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
	b2Vec2 org=this->getOrigin();
	m_Sprite.setOrigin(org.x, org.y);
	if (m_Anim)
		m_Anim->draw(m_Sprite, m_Size, m_Time, m_Looped);
	m_Time += dt;
}
