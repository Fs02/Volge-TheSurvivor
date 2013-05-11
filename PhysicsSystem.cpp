#include "stdafx.h"
#include "PhysicsSystem.hpp"
#include "Entity/Entity.hpp"

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

	if(userDataA && userDataB)
	{
		Entity* entA=(Entity*)userDataA;
		Entity* entB=(Entity*)userDataB;

		entA->onCollisionBegin(entB);
		entB->onCollisionBegin(entA);
	}
}

void PhysicsSystem::EndContact(b2Contact* contact)
{
	b2Fixture* fixA		= contact->GetFixtureA();
	b2Fixture* fixB		= contact->GetFixtureB();
	void* userDataA		= fixA->GetBody()->GetUserData();
	void* userDataB		= fixB->GetBody()->GetUserData();

	if(userDataA && userDataB)
	{
		Entity* entA=(Entity*)userDataA;
		Entity* entB=(Entity*)userDataB;

		entA->onCollisionEnd(entB);
		entB->onCollisionEnd(entA);
	}
}
