#include "PhysicsSystem.hpp"

PhysicsSystem* PhysicsSystem::instance	= nullptr;

PhysicsSystem* PhysicsSystem::getSingleton()
{
	if (instance == nullptr)
		instance = new PhysicsSystem();

	return instance;
}

PhysicsSystem* PhysicsSystem::initialise()
{
	return getSingleton();
}

void PhysicsSystem::deinitialise()
{
	delete instance;
}

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

Entity* PhysicsSystem::rayCast(const b2Vec2& origin, const b2Vec2& end)
{
	b2Fixture* fix=this->internalClosestRayCastResult(origin, end);
	if(!fix)
		return nullptr;
	Entity* ent=(Entity*)(fix->GetBody()->GetUserData());
	return ent;
}
