#pragma once

#include "stdafx.h"
#include "MadEngine\MadEngine.hpp"
#include "CEntity\CWaepon\CBullet.hpp"
#include "Entity\Human\Soldier.hpp"
#include "Entity\Zombie\Zombie.hpp"

class PhysicsSystem 
	: b2ContactListener
	//public Mad::Interface::IPhysicsSystem
{
public:
	PhysicsSystem(b2World* World)
		//: Mad::Interface::IPhysicsSystem(World)
	{
		World->SetContactListener(this);
	}

	~PhysicsSystem()
	{}

	std::vector<CEntity::CBullet*> m_BulletBuffer;
	void BeginContact(b2Contact* contact)
	{
		b2Fixture* fixA		= contact->GetFixtureA();
		b2Fixture* fixB		= contact->GetFixtureB();
		void* userDataA		= fixA->GetBody()->GetUserData();
		void* userDataB		= fixB->GetBody()->GetUserData();

		if ((0 == (fixA->GetFilterData().categoryBits & CEntity::CENSOR)) || (0 == (fixB->GetFilterData().categoryBits & CEntity::CENSOR)))
		{
			if (fixA->GetFilterData().categoryBits	== CEntity::BULLET)
			{
				if (std::find(m_BulletBuffer.begin(), m_BulletBuffer.end(), static_cast<CEntity::CBullet*>(userDataA)) == m_BulletBuffer.end())
					m_BulletBuffer.push_back(static_cast<CEntity::CBullet*>(userDataA));
			}

			if (fixB->GetFilterData().categoryBits	== CEntity::BULLET)
			{
				if (std::find(m_BulletBuffer.begin(), m_BulletBuffer.end(), static_cast<CEntity::CBullet*>(userDataB)) == m_BulletBuffer.end())
					m_BulletBuffer.push_back(static_cast<CEntity::CBullet*>(userDataB));
			}

			if ((0 != (fixA->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixB->GetFilterData().categoryBits&CEntity::SOLDIER)))
				static_cast<Entity::Zombie*>(userDataA)->addTarget(fixB->GetBody());
			
			if ((0 != (fixB->GetFilterData().categoryBits&(CEntity::ZOMBIE|CEntity::CENSOR))) && (0 != (fixA->GetFilterData().categoryBits&CEntity::SOLDIER)))
				static_cast<Entity::Zombie*>(userDataB)->addTarget(fixA->GetBody());
		}
	}

	void EndContact(b2Contact* contact)
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

	void processBuffer()
	{ 
		for (auto it = m_BulletBuffer.begin(); it != m_BulletBuffer.end(); ++it)
		{
			CEntity::CBullet* bullet	= *it;
			delete bullet;
		}
		m_BulletBuffer.clear();
	}
};