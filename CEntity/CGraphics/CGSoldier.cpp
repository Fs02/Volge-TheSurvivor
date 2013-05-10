#include "stdafx.h"
#include "CGSoldier.hpp"

CEntity::CGraphics::CGSoldier::CGSoldier(PhysicsSystem* physicsInstance)
	: CEntity::ICEntity(physicsInstance)
{
	m_State			= 0;

	m_AniSprite.setTexture("soldier");
	m_AniSprite.setFrameSize(128,128);
	m_AniSprite.setOrigin(64,80);
	m_AniSprite.setLoopSpeed(10);
	m_AniSprite.setInvertSprite(true);
}

CEntity::CGraphics::CGSoldier::~CGSoldier()
{
}

void CEntity::CGraphics::CGSoldier::update(float deltaTime)
{
	if (( 0 != (m_State & STATE::FORWARD)) || (0 != (m_State & STATE::BACKWARD)))
	{
		if (0 != (m_State & STATE::ATTACK))
		{
			if (!m_AniSprite.isPlaying(18,25))
				m_AniSprite.play(18,25);
		} else {
			if (!m_AniSprite.isPlaying(10,17))
				m_AniSprite.play(10,17);
		}
	} 
	//Check if it is not idle
	else if (0 != (m_State & STATE::STEADY))
	{
		if (0 != (m_State & STATE::ATTACK))
		{
			if (!m_AniSprite.isPlaying(2,9))
				m_AniSprite.play(2,9);
		} else {
			if (!m_AniSprite.isPlaying(1,1))
				m_AniSprite.play(1,1);
		}
	}
	else
	{
		if (!m_AniSprite.isPlaying(0,0))
			m_AniSprite.play(0,0);
	}

	m_AniSprite.setPosition(m_Pos.x * RATIO, m_Pos.y * RATIO);
	m_AniSprite.setRotation(m_Angle * RADTODEG);
	m_AniSprite.update(deltaTime);
}

void CEntity::CGraphics::CGSoldier::setParams(const b2Vec2& pos, float angle, int state)
{
	m_Pos			= pos;
	m_Angle			= angle;
	m_State			= state;
}

void CEntity::CGraphics::CGSoldier::draw()
{
	m_AniSprite.draw();
}