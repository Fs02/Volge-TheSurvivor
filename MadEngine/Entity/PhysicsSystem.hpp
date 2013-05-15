#pragma once

#include <Box2D/Box2D.h>
#include "../Interface/IPhysicsSystem.hpp"
#include "Entity.hpp"

class PhysicsSystem 
	: b2ContactListener,
	  public Mad::Interface::IPhysicsSystem
{
private:
    static PhysicsSystem* instance;
    PhysicsSystem();
	~PhysicsSystem();

public:
	static PhysicsSystem* getSingleton();
	static PhysicsSystem* initialise();
	static void deinitialise();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	Entity* rayCast(const b2Vec2& origin, const b2Vec2& end);
};
