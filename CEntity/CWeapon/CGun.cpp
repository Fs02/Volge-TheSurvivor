#include "stdafx.h"
#include "CGun.hpp"

CEntity::CWeapon::CGun::CGun(b2World* world, const std::string& name, float spr, int totalBullet,int magCapacity, float loadTime)
	:CEntity::CWeapon::ICWaepon(CEntity::CWeapon::GUN)
{
	m_World			= world;
	m_Name			= name;
	m_Spr			= spr;
	m_TotalBullet	= totalBullet;
	m_MagBullet		= 0;
	m_MagCapacity	= magCapacity;
	m_LoadTime		= loadTime;
	m_TimeLastAction= 0;
	m_CockSound.setBuffer(*Mad::Manager::Resource::getSoundBuffer("gun_cock"));
	m_ShootSound.setBuffer(*Mad::Manager::Resource::getSoundBuffer("gun_shoot"));
	m_NoAmmoSound.setBuffer(*Mad::Manager::Resource::getSoundBuffer("gun_noammo"));
}

CEntity::CWeapon::CGun::~CGun()
{
	m_World			= nullptr;
}

void CEntity::CWeapon::CGun::attack(const b2Vec2& normal, const b2Vec2& pos, float rot)
{
	m_isShooting	= false;
	float time	= m_Clock.getElapsedTime().asSeconds();

	if (m_MagBullet > 0)
	{
		m_isShooting	= true;
		if ((time - m_TimeLastAction) > m_Spr)
		{
			m_ShootSound.play();
			new CEntity::CBullet(m_World, normal, pos, rot);
			m_TimeLastAction	= time;
			m_MagBullet			-=1;
		}
	}

	else if ((m_MagBullet == 0) && (m_TotalBullet > 0))
	{
		if ((m_CockSound.getStatus() != m_CockSound.Playing) && ((time - m_TimeLastAction) < 1.f))
			m_CockSound.play();

		m_isShooting	= false;
		if ((time - m_TimeLastAction) > m_LoadTime)
		{
			if (m_TotalBullet > m_MagCapacity)
			{
				m_MagBullet			= m_MagCapacity;
			}
			else
			{
				m_MagBullet			= m_TotalBullet;
			}

			m_TotalBullet			= m_TotalBullet - m_MagBullet;
			std::cout<<m_TotalBullet<<" | "<<m_MagBullet<<std::endl;
			m_TimeLastAction		= 0;
			m_Clock.restart();
		}
	}
	else
	{
		m_isShooting		= false;
		if (m_NoAmmoSound.getStatus() != m_NoAmmoSound.Playing)
			m_NoAmmoSound.play();
	}
}

void CEntity::CWeapon::CGun::reload()
{
	if (m_CockSound.getStatus() != m_CockSound.Playing)
	m_CockSound.play();
	m_TotalBullet		+= m_MagBullet;
	m_MagBullet			= 0;
}

bool CEntity::CWeapon::CGun::isShooting()
{
	return m_isShooting;
}