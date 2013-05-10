#include "stdafx.h"
#include "PhysicsSystem.hpp"

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
}

void PhysicsSystem::EndContact(b2Contact* contact)
{
	b2Fixture* fixA		= contact->GetFixtureA();
	b2Fixture* fixB		= contact->GetFixtureB();
	void* userDataA		= fixA->GetBody()->GetUserData();
	void* userDataB		= fixB->GetBody()->GetUserData();
}
