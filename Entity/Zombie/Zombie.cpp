#include "stdafx.h"
#include "Zombie.hpp"

Entity::Zombie::Zombie(PhysicsSystem* physicsInstance)
	:CEntity::CSkeleton::Human(physicsInstance, CEntity::ZOMBIE),
	CEntity::CHealth(physicsInstance, 100),
	CEntity::CAI::AIZombie(physicsInstance)
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

void Entity::Zombie::update(float deltaTime)
{
	CEntity::CAI::AIZombie::update(deltaTime);
	int state		= getAIState();

	CEntity::CSkeleton::Human::setState(state);
	this->CEntity::CSkeleton::Human::update(deltaTime);
	this->CEntity::CHealth::update(deltaTime);
	this->CEntity::CAI::AIZombie::update(deltaTime);
	
	//weapon attack


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

void Entity::Zombie::draw()
{
	m_AniSprite.draw();
}
