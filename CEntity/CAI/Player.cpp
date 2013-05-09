#include "stdafx.h"
#include "Player.hpp"

CEntity::CAI::Player::Player(PhysicsSystem* physicsInstance)
	: CEntity::ICEntity(physicsInstance)
{
	m_Controller		= Mad::Manager::Controller::getSingleton();
	int m_State			= STATE::IDLE;
}

CEntity::CAI::Player::~Player()
{
}

int CEntity::CAI::Player::getAIState()
{
	return m_State;
}

void CEntity::CAI::Player::setAIState(int state)
{
	m_State				= m_State|state;
}

void CEntity::CAI::Player::unsetAIState(int state)
{
	m_State				= m_State & ~state;
}

void CEntity::CAI::Player::update(float deltaTime)
{
	//reset all states back to idle
	resetState();
	m_TotalTime			+= deltaTime;

	//UPDATE STATE
	if (m_Controller->getControl("forward"))
		setAIState(STATE::FORWARD);
	else if (m_Controller->getControl("backward"))
		setAIState(STATE::BACKWARD);
	else;

	if (m_Controller->getControl("left"))
		setAIState(STATE::LEFT);
	else if (m_Controller->getControl("right"))
		setAIState(STATE::RIGHT);
	else;

	if (m_Controller->getControl("reload"))
		setAIState(STATE::RELOAD);
	else if (m_Controller->getControl("attack"))
		setAIState(STATE::ATTACK);
	else if (m_Controller->getControl("throw"))
		setAIState(STATE::THROW);
	else;

	//Check if player need to idle
	if ((0 != (m_prevState & STATE::STEADY)) && (m_TotalTime > 5) || ((m_prevState == m_State) == STATE::IDLE))
	{
		resetState();	//set back to idle
	}
	else
		setAIState(STATE::STEADY);

	//Reset Clock if state has been changed
	if (m_State != m_prevState)
	{
		m_TotalTime			= 0;
	}
	m_prevState		= m_State;
}

void CEntity::CAI::Player::onCollisionBegin(Entity::IEntity* other)
{
}

void CEntity::CAI::Player::onCollisionEnd(Entity::IEntity* other)
{
}

void CEntity::CAI::Player::resetState()
{
	m_State		= STATE::IDLE;
}