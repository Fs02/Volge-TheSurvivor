#include "Gun.hpp"

/*
 * Item::GunMagazine
 */

Item::GunMagazine::GunMagazine(const std::string &gunName)
    :m_Name(gunName + " magazine")
{
}

Item::ItemClass::Enum Item::GunMagazine::getClass() const
{
    return ItemClass::PickUp;
}

std::string Item::GunMagazine::getName() const
{
    return m_Name;
}

bool Item::GunMagazine::compare(const IItem *other) const
{
    const GunMagazine* gm=dynamic_cast<const GunMagazine*>(other);
    if(!gm)
        return false;

    return m_Name == gm->m_Name;
}

/*
 * Item::Gun
 */

Item::Gun::Gun(const std::string& name, int damage, int magCap,
		int numBullets, float reloadTime, float shootDelay)
		: m_Name(name), m_Damage(damage), m_MagCap(magCap), m_NumBullets(
				numBullets), m_ReloadTime(reloadTime), m_ShootDelayTime(
				shootDelay), m_State(GunState::ReadyToShoot), m_Time(0), m_LastActionTime(
				0)
{
	if(m_NumBullets == 0)
		m_State=GunState::EmptyMag;
}

Item::ItemClass::Enum Item::Gun::getClass() const
{
	return ItemClass::Weapon;
}

std::string Item::Gun::getName() const
{
	return m_Name;
}

bool Item::Gun::compare(const IItem *other) const
{
    const Gun* gun=dynamic_cast<const Gun*>(other);
    if(!gun)
        return false;

    return gun->m_Name == m_Name;
}

int Item::Gun::getBulletDamage() const
{
	return m_Damage;
}

int Item::Gun::getMagCapacity() const
{
	return m_MagCap;
}

int Item::Gun::getNumBulletsInMag() const
{
	return m_NumBullets;
}

float Item::Gun::getReloadTime() const
{
	return m_ReloadTime;
}

float Item::Gun::getShootDelayTime() const
{
	return m_ShootDelayTime;
}

Item::GunState::Enum Item::Gun::getState() const
{
	return m_State;
}

bool Item::Gun::shoot()
{
	if(m_State != GunState::ReadyToShoot)
		return false;

	m_LastActionTime=m_Time;
	--m_NumBullets;
	if(m_NumBullets == 0)
		m_State=GunState::EmptyMag;
	else
		m_State=GunState::ShootDelay;

	return true;
}

bool Item::Gun::reloadMag()
{
    if(m_State != GunState::ReadyToShoot && m_State != GunState::EmptyMag)
		return false;

	m_State=GunState::Reloading;
    m_NumBullets=m_MagCap;
	m_LastActionTime=m_Time;
	return true;
}

void Item::Gun::update(float dt)
{
	m_Time+=dt;
	switch(m_State)
	{
	case GunState::ShootDelay:
		{
			if(m_Time - m_LastActionTime >= m_ShootDelayTime)
				m_State=GunState::ReadyToShoot;
		}break;
	case GunState::Reloading:
		{
			if(m_Time - m_LastActionTime >= m_ReloadTime)
				m_State=GunState::ReadyToShoot;
		}break;
	default:
		break;
	}
}
