#include "stdafx.h"
#include "Soldier.hpp"

Entity::Soldier::Soldier(PhysicsSystem* physicsInstance)
	:CEntity::CSkeleton::Human(physicsInstance, CEntity::SOLDIER),
	CEntity::CHealth(physicsInstance, 100),
	CEntity::CAI::Player(physicsInstance),
	CEntity::CGraphics::CGSoldier(physicsInstance)
{
	m_Controller		= Mad::Manager::Controller::getSingleton();

	m_Body->SetUserData(this);

	m_Waepon			= new CEntity::CWeapon::CGun(physicsInstance,"m16",0.21f ,120,30,1);

	m_FootSteps.setBuffer(*Mad::Manager::Resource::getSoundBuffer("footsteps"));
	m_FootSteps.setVolume(30);
	m_FootSteps.setLoop(true);
}

Entity::Soldier::~Soldier()
{
}

void Entity::Soldier::update(float deltaTime)
{
	CEntity::CAI::Player::update(deltaTime);
	int state		= getAIState();

	CEntity::CSkeleton::Human::setParams(state);
	CEntity::CSkeleton::Human::update(deltaTime);

	if (0 != (state & STATE::ATTACK))
		m_Waepon->attack(m_Body->GetWorldVector(b2Vec2(0.f,1.f)), m_Body->GetWorldPoint(b2Vec2(-0.6f,1.f)), getAngle());
	if (!m_Waepon->isShooting())
		unsetAIState(STATE::ATTACK);

	if (0 != (state & STATE::RELOAD))
		m_Waepon->reload();

	CEntity::CGraphics::CGSoldier::setParams(this->getPosition(), this->getAngle(), state);
	CEntity::CGraphics::CGSoldier::update(deltaTime);
	
	//TODO: Apply code below for Component Sound
	if (( 0 != (state & STATE::FORWARD)) || (0 != (state & STATE::BACKWARD)))
	{
		if (0 != (state & STATE::ATTACK))
		{
			if (m_FootSteps.getStatus() != m_FootSteps.Playing)
				m_FootSteps.play();
		} else {
			if (m_FootSteps.getStatus() != m_FootSteps.Playing)
				m_FootSteps.play();
		}
	} 
	//Check if it is not idle
	else if (0 != (state & STATE::STEADY))
	{
		if (0 != (state & STATE::ATTACK))
		{
			if (m_FootSteps.getStatus() == m_FootSteps.Playing)
				m_FootSteps.pause();
		} else {
			if (m_FootSteps.getStatus() == m_FootSteps.Playing)
				m_FootSteps.pause();
		}
	}
	else
	{
		if (m_FootSteps.getStatus() == m_FootSteps.Playing)
			m_FootSteps.pause();
	}
}

void Entity::Soldier::onCollisionBegin(Entity::IEntity* other)
{
}

void Entity::Soldier::onCollisionEnd(Entity::IEntity* other)
{
}

void Entity::Soldier::onDamage(Entity::IEntity* other, int damage)
{
}
