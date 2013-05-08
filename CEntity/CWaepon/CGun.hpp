#pragma once

#include "..\..\stdafx.h"
#include "..\ICWaepon.hpp"
#include "CBullet.hpp"
#include "..\..\MadEngine\MadEngine.hpp"

namespace CEntity
{
	namespace CWaepon
	{
		class CGun
			: public CEntity::CWaepon::ICWaepon
		{
		private:
			std::string m_Name;
			b2World* m_World;
			int m_TotalBullet, m_MagCapacity, m_MagBullet;
			float m_Spr, m_LoadTime, m_TimeLastAction;
			sf::Clock m_Clock;
			bool m_isShooting;

			sf::Sound m_CockSound, m_ShootSound, m_NoAmmoSound;

		public:
			CGun(b2World* world, const std::string& name, float spr, int totalBullet, int magCapacity, float loadTime);
			~CGun();
			void attack(const b2Vec2& normal, const b2Vec2& pos, float rot);
			void reload();

			bool isShooting();
		};
	}
}