#include "stdafx.h"
#include "ICEntity.hpp"

CEntity::ICEntity::ICEntity(PhysicsSystem* instance)
{
	m_PhysicsSytem		= instance;
}

CEntity::ICEntity::~ICEntity()
{
}