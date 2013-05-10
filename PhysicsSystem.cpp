#include "stdafx.h"
#include "PhysicsSystem.hpp"
#include "CEntity/ICEntity.hpp"

PhysicsSystem::PhysicsSystem()
	: Mad::Interface::IPhysicsSystem(new b2World(b2Vec2(0, 0)))
{
	m_World->SetContactListener(this);
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA		= contact->GetFixtureA();
	b2Fixture* fixB		= contact->GetFixtureB();
	void* userDataA		= fixA->GetBody()->GetUserData();
	void* userDataB		= fixB->GetBody()->GetUserData();

	if ((0 == (fixA->GetFilterData().categoryBits & CEntity::CENSOR)) || (0 == (fixB->GetFilterData().categoryBits & CEntity::CENSOR)))
	{
		if ((0 != (fixA->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixB->GetFilterData().categoryBits&CEntity::SOLDIER)))
			static_cast<Entity::Zombie*>(userDataA)->addTarget(fixB->GetBody());

		if ((0 != (fixB->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixA->GetFilterData().categoryBits&CEntity::SOLDIER)))
			static_cast<Entity::Zombie*>(userDataB)->addTarget(fixA->GetBody());
	}
}

void PhysicsSystem::EndContact(b2Contact* contact)
{
	b2Fixture* fixA		= contact->GetFixtureA();
	b2Fixture* fixB		= contact->GetFixtureB();
	void* userDataA		= fixA->GetBody()->GetUserData();
	void* userDataB		= fixB->GetBody()->GetUserData();

	if ((0 == (fixA->GetFilterData().categoryBits & CEntity::CENSOR)) || (0 == (fixB->GetFilterData().categoryBits & CEntity::CENSOR)))
	{
		if ((0 != (fixA->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixB->GetFilterData().categoryBits&CEntity::SOLDIER)))
			static_cast<Entity::Zombie*>(userDataA)->removeTarget(fixB->GetBody());

		if ((0 != (fixB->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixA->GetFilterData().categoryBits&CEntity::SOLDIER)))
			static_cast<Entity::Zombie*>(userDataB)->removeTarget(fixA->GetBody());
	}
}

Entity::IEntity* PhysicsSystem::rayCast(const b2Vec2& start, const b2Vec2& end)
{
	b2Fixture* fix=this->internalClosestRayCastResult(start, end);
	CEntity::ICEntity* cent=(CEntity::ICEntity*)fix->GetBody()->GetUserData();
	Entity::IEntity* ent=dynamic_cast<Entity::IEntity*>(cent);
	return ent;
}
