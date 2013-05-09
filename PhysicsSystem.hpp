#pragma once

#include "stdafx.h"
#include "MadEngine/MadEngine.hpp"
#include "CEntity/CWeapon/CBullet.hpp"
#include "Entity/Human/Soldier.hpp"
#include "Entity/Zombie/Zombie.hpp"

class PhysicsSystem 
	: b2ContactListener,
	  public Mad::Interface::IPhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	Entity::IEntity* rayCast(const b2Vec2& start, const b2Vec2& end);
};
