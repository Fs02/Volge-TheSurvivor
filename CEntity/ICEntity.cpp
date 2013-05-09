#include "stdafx.h"
#include "ICEntity.hpp"

CEntity::ICEntity::ICEntity(PhysicsSystem* instance)
{
	m_PhysicsSystem		= instance;
}

CEntity::ICEntity::~ICEntity()
{
}

void CEntity::ICEntity::onCollisionBegin(Entity::IEntity* other)
{
}

void CEntity::ICEntity::onCollisionEnd(Entity::IEntity* other)
{
}

void CEntity::ICEntity::onDamage(Entity::IEntity* other, int damage)
{
}
