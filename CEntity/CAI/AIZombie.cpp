#include "stdafx.h"
#include "AIZombie.hpp"

CEntity::CAI::AIZombie::AIZombie()
{	
	m_State				= STATE::IDLE;
	m_Bodyptr				= nullptr;
}

CEntity::CAI::AIZombie::~AIZombie()
{
}

int CEntity::CAI::AIZombie::getAIState()
{
	return m_State;
}

void CEntity::CAI::AIZombie::setAIState(int state)
{
	m_State				= m_State|state;
}

void CEntity::CAI::AIZombie::unsetAIState(int state)
{
	m_State				= m_State & ~state;
}

void CEntity::CAI::AIZombie::setAIBody(b2Body* body)
{
	m_Bodyptr			= body;
}

void CEntity::CAI::AIZombie::addTarget(b2Body* body)
{
	if (std::find(m_TargetList.begin(), m_TargetList.end(), body) == m_TargetList.end())
		m_TargetList.push_back(body);
}

void CEntity::CAI::AIZombie::removeTarget(b2Body* body)
{
	auto it = std::find(m_TargetList.begin(), m_TargetList.end(), body);
	if ( it != m_TargetList.end());
		//m_TargetList.erase(it);
}

b2Vec2 CEntity::CAI::AIZombie::getNearestTarget()
{
	if (m_TargetList.empty())
		return m_Bodyptr->GetPosition();

	b2Vec2 nearPos		= m_TargetList[0]->GetPosition();
	float nearDis		= nearPos.Length();
	
	for (auto it = m_TargetList.begin(); it != m_TargetList.end(); ++it)
	{
		if ((*it)->GetPosition().Length() < nearDis)
		{
			nearPos			= (*it)->GetPosition();
			nearDis			= nearPos.Length();
		}
	}
	return nearPos;
}

void CEntity::CAI::AIZombie::updateAI()
{
	if (m_Bodyptr == nullptr)
		throw Mad::Manager::Exceptions::BadMemoryAllocation("Invalid Pointer !");

	resetState();
	float elapsedTime	= m_Clock.getElapsedTime().asSeconds();

	b2Vec2 localVector	= m_Bodyptr->GetLocalPoint(getNearestTarget());
	//UPDATE STATE

	//Foward or attack
	if (localVector.Length() > 1.f)
		setAIState(STATE::FORWARD);
	else 
		setAIState(STATE::ATTACK);

	//Where to Turn 
	float angle			= std::atan2(localVector.x, localVector.y);
	if (angle > (5.f * DEGTORAD))
		setAIState(STATE::LEFT);
	else if (angle < (-5.f * DEGTORAD))
		setAIState(STATE::RIGHT);
	else;

	//Check if it's time to idle
	if ((0 != (m_prevState & STATE::STEADY)) && (elapsedTime > 5) || ((m_prevState == m_State) == STATE::IDLE))
		resetState();
	else
		setAIState(STATE::STEADY);

	//Reset Clock if state has been changed
	if (m_State != m_prevState)
	{
		m_Clock.restart();
	}
	m_prevState			=  m_State;
}

void CEntity::CAI::AIZombie::resetState()
{
	m_State				= STATE::IDLE;
}
