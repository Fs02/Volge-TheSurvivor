#pragma once

#include <Box2D/Box2D.h>
#include "../Interface/IPhysicsSystem.hpp"
#include "Entity/Entity.hpp"

class PhysicsSystem 
	: b2ContactListener,
	  public Mad::Interface::IPhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	Entity* rayCast(const b2Vec2& origin, const b2Vec2& end);
};
