#include "stdafx.h"
#include "CGZombie.hpp"

CEntity::CGraphics::CGZombie::CGZombie(PhysicsSystem* physicsInstance)
	: CEntity::ICEntity(physicsInstance)
{
	m_AniSprite.setTexture("zombie");
	m_AniSprite.setFrameSize(128,128);
	m_AniSprite.setLoopSpeed(10);
	m_AniSprite.setInvertSprite(true);
	m_AniSprite.play();
}

CEntity::CGraphics::CGZombie::~CGZombie()
{
}

void CEntity::CGraphics::CGZombie::update(float deltaTime)
{
	if ( 0 != (m_State & STATE::FORWARD))
	{
		if (!m_AniSprite.isPlaying(4,11))
			m_AniSprite.play(4,11);
	} 
	//Check if it is not idle
	else if (0 != (m_State & STATE::ATTACK))
	{
		if (!m_AniSprite.isPlaying(12,21))
			m_AniSprite.play(12,21);
	} 
	else if (0 != (m_State & STATE::IDLE))
	{
		if (m_AniSprite.isPlaying(0,3))
			m_AniSprite.play(0,3);
	}
	
	m_AniSprite.setPosition(m_Pos.x * RATIO, m_Pos.y * RATIO);
	m_AniSprite.setRotation(m_Angle * RADTODEG);
	m_AniSprite.update(deltaTime);
}

void CEntity::CGraphics::CGZombie::setParams(const b2Vec2& pos, float angle, int state)
{
	m_Pos			= pos;
	m_Angle			= angle;
	m_State			= state;
}

void CEntity::CGraphics::CGZombie::draw()
{
	m_AniSprite.draw();
}