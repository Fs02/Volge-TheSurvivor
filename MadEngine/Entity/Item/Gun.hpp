#pragma once

#include "IItem.hpp"

namespace Item
{
	namespace GunState
	{
		enum Enum{ ReadyToShoot, ShootDelay, Reloading, EmptyMag };
	}

    class GunMagazine : public IItem
    {
    public:
        GunMagazine(const std::string& gunName);

        ItemClass::Enum getClass() const;
        std::string getName() const;
        bool compare(const IItem *other) const;

    private:
        std::string m_Name;
    };

	class Gun : public IItem
	{
	public:
		Gun(const std::string& name, int damage, int magCap, int numBullets, float reloadTime, float shootDelay);

		ItemClass::Enum getClass() const;
        std::string getName() const;
        bool compare(const IItem *other) const;
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
