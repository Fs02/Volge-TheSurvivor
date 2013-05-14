#pragma once

#include "stdafx.h"
#include "MadEngine/MadEngine.hpp"
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
