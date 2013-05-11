#pragma once

#include "IItem.hpp"

namespace Item
{
	namespace GunState
	{
		enum Enum{ ReadyToShoot, ShootDelay, Reloading, EmptyMag };
	}

	class Gun : public IItem
	{
	public:
		Gun(const std::string& name, int damage, int magCap, int numBullets, float reloadTime, float shootDelay);

		ItemClass::Enum getClass() const;
		const std::string& getName() const;
		int getBulletDamage() const;
		int getMagCapacity() const;
		int getNumBulletsInMag() const;
		float getReloadTime() const;
		float getShootDelayTime() const;

		GunState::Enum getState() const;
		bool shoot();
		bool reloadMag();

		void update(float dt);

	private:
		std::string m_Name;
		int m_Damage;
		int m_MagCap;
		int m_NumBullets;
		float m_ReloadTime;
		float m_ShootDelayTime; // time between two shots
		GunState::Enum m_State;
		float m_Time, m_LastActionTime;
	};
}
