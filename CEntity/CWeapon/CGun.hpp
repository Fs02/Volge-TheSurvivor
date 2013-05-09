#pragma once

#include "../../stdafx.h"
#include "CBullet.hpp"
#include "../../MadEngine/MadEngine.hpp"
#include "../ICEntity.hpp"

namespace CEntity
{
	namespace CWeapon
	{
		class CGun
			: public CEntity::ICEntity
		{
		private:
			std::string m_Name;
			int m_TotalBullet, m_MagCapacity, m_MagBullet;
			float m_Spr, m_LoadTime, m_TimeLastAction;
			sf::Clock m_Clock;
			bool m_isShooting;

			sf::Sound m_CockSound, m_ShootSound, m_NoAmmoSound;

		public:
			CGun(PhysicsSystem* physicsIntance, const std::string& name, float spr, int totalBullet, int magCapacity, float loadTime);
			~CGun();
			void attack(const b2Vec2& normal, const b2Vec2& pos, float rot);
			void reload();

			bool isShooting();

			void update(float deltaTime);
			void onCollisionBegin(Entity::IEntity* other);
			void onCollisionEnd(Entity::IEntity* other);
		};
	}
}
