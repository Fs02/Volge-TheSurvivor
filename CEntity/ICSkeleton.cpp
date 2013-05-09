#include "stdafx.h"
#include "ICSkeleton.hpp"

CEntity::ICSkeleton::ICSkeleton()
{
	m_Controller		= Mad::Manager::Controller::getSingleton();
}

CEntity::ICSkeleton::~ICSkeleton()
{
	m_Body->GetWorld()->DestroyBody(m_Body);
}

const b2Vec2& CEntity::ICSkeleton::getPosition()
{
	return m_Body->GetPosition();
}

b2Vec2 CEntity::ICSkeleton::getNormal()
{
	return m_Body->GetWorldVector(b2Vec2(0,1));
}

float CEntity::ICSkeleton::getAngle()
{
	return m_Body->GetAngle();
}
