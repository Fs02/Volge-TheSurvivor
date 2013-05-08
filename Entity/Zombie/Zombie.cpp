#include "stdafx.h"
#include "Zombie.hpp"

Entity::Zombie::Zombie(b2World* World)
	:CEntity::CSkeleton::Human(World, CEntity::ZOMBIE),
	CEntity::CHealth(100)
{
	m_Body->SetUserData(this);
	setSpeed(0.5f);
	setAIBody(m_Body);

	m_AniSprite.setTexture("zombie");
	m_AniSprite.setFrameSize(128,128);
	m_AniSprite.setLoopSpeed(10);
	m_AniSprite.setInvertSprite(true);
	m_AniSprite.play();
}

Entity::Zombie::~Zombie()
{
}

void Entity::Zombie::update()
{
	updateAI();
	int state		= getAIState();
	updateSkeleton(state);
	
	//waepon attack


	if ( 0 != (state & STATE::FORWARD))
	{
		if (!m_AniSprite.isPlaying(4,11))
			m_AniSprite.play(4,11);
	} 
	//Check if it is not idle
	else if (0 != (state & STATE::ATTACK))
	{
		if (!m_AniSprite.isPlaying(12,21))
			m_AniSprite.play(12,21);
	} 
	else if (0 != (state & STATE::IDLE))
	{
		if (m_AniSprite.isPlaying(0,3))
			m_AniSprite.play(0,3);
	}
	
	m_AniSprite.setPosition(getPosition().x * RATIO, getPosition().y * RATIO);
	m_AniSprite.setRotation(getAngle() * RADTODEG);
	m_AniSprite.update();
}

void Entity::Zombie::draw()
{
	m_AniSprite.draw();
}