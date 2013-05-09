#include "stdafx.h"
#include "Soldier.hpp"

Entity::Soldier::Soldier(b2World* World)
	:CEntity::CSkeleton::Human(World, CEntity::SOLDIER),
	CEntity::CHealth(100),
	CEntity::CAI::Player()
{
	m_Controller		= Mad::Manager::Controller::getSingleton();

	m_Body->SetUserData(this);
	m_AniSprite.setTexture("soldier");
	m_AniSprite.setFrameSize(128,128);
	m_AniSprite.setOrigin(64,80);
	m_AniSprite.setLoopSpeed(10);
	m_AniSprite.setInvertSprite(true);
	m_World				= World;
	m_Waepon			= new CEntity::CWeapon::CGun(World,"m16",0.21f ,120,30,1);

	m_FootSteps.setBuffer(*Mad::Manager::Resource::getSoundBuffer("footsteps"));
	m_FootSteps.setVolume(30);
	m_FootSteps.setLoop(true);
}

Entity::Soldier::~Soldier()
{
}

void Entity::Soldier::update()
{
	updateAI();
	int state		= getAIState();
	updateSkeleton(state);
	
	if (0 != (state & STATE::ATTACK))
		m_Waepon->attack(m_Body->GetWorldVector(b2Vec2(0.f,1.f)), m_Body->GetWorldPoint(b2Vec2(-0.6f,1.f)), getAngle());
	if (!m_Waepon->isShooting())
		unsetAIState(STATE::ATTACK);

	if (0 != (state & STATE::RELOAD))
		m_Waepon->reload();
	
	//Check wether to use walk animation or not
	if (( 0 != (state & STATE::FORWARD)) || (0 != (state & STATE::BACKWARD)))
	{
		if (0 != (state & STATE::ATTACK))
		{
			if (!m_AniSprite.isPlaying(18,25))
				m_AniSprite.play(18,25);
			if (m_FootSteps.getStatus() != m_FootSteps.Playing)
				m_FootSteps.play();
		} else {
			if (!m_AniSprite.isPlaying(10,17))
				m_AniSprite.play(10,17);
			if (m_FootSteps.getStatus() != m_FootSteps.Playing)
				m_FootSteps.play();
		}
	} 
	//Check if it is not idle
	else if (0 != (state & STATE::STEADY))
	{
		if (0 != (state & STATE::ATTACK))
		{
			if (!m_AniSprite.isPlaying(2,9))
				m_AniSprite.play(2,9);
			if (m_FootSteps.getStatus() == m_FootSteps.Playing)
				m_FootSteps.pause();
		} else {
			if (!m_AniSprite.isPlaying(1,1))
				m_AniSprite.play(1,1);
			if (m_FootSteps.getStatus() == m_FootSteps.Playing)
				m_FootSteps.pause();
		}
	}
	else
	{
		if (!m_AniSprite.isPlaying(0,0))
			m_AniSprite.play(0,0);
		if (m_FootSteps.getStatus() == m_FootSteps.Playing)
			m_FootSteps.pause();
	}

	m_AniSprite.setPosition(getPosition().x * RATIO, getPosition().y * RATIO);
	m_AniSprite.setRotation(getAngle() * RADTODEG);
	m_AniSprite.update();
}

void Entity::Soldier::draw()
{
	m_AniSprite.draw();
}