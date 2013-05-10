#include "stdafx.h"
#include "Zombie.hpp"

Entity::Zombie::Zombie(PhysicsSystem* physicsInstance)
	:CEntity::CSkeleton::Human(physicsInstance, CEntity::ZOMBIE),
	CEntity::CHealth(physicsInstance, 100),
	CEntity::CAI::AIZombie(physicsInstance),
	CEntity::CGraphics::CGZombie(physicsInstance)
{
	m_Body->SetUserData(this);
	setSpeed(0.5f);
	setAIBody(m_Body);
}

Entity::Zombie::~Zombie()
{
}

void Entity::Zombie::update(float deltaTime)
{
	this->CEntity::CAI::AIZombie::update(deltaTime);
	int state		= getAIState();

	this->CEntity::CSkeleton::Human::setParams(state);
	this->CEntity::CGraphics::CGZombie::setParams(this->getPosition(), this->getAngle(), state);

	this->CEntity::CSkeleton::Human::update(deltaTime);
	this->CEntity::CHealth::update(deltaTime);
	this->CEntity::CAI::AIZombie::update(deltaTime);
	this->CEntity::CGraphics::CGZombie::update(deltaTime);
	
	//Todo : Component Sound
}

void Entity::Zombie::onCollisionBegin(Entity::IEntity* other)
{
	this->CEntity::CSkeleton::Human::onCollisionBegin(other);
	this->CEntity::CHealth::onCollisionBegin(other);
	this->CEntity::CAI::AIZombie::onCollisionBegin(other);
}

void Entity::Zombie::onCollisionEnd(Entity::IEntity* other)
{
	this->CEntity::CSkeleton::Human::onCollisionEnd(other);
	this->CEntity::CHealth::onCollisionEnd(other);
	this->CEntity::CAI::AIZombie::onCollisionEnd(other);
}

void Entity::Zombie::onDamage(Entity::IEntity* other, int damage)
{
	this->CEntity::CSkeleton::Human::onDamage(other, damage);
	this->CEntity::CHealth::onDamage(other, damage);
	this->CEntity::CAI::AIZombie::onDamage(other, damage);
}
