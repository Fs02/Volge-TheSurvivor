#include "stdafx.h"
#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int maxHP, int initHP, float recoveryTime)
	:m_Owner(nullptr), m_MaxHP(maxHP), m_HP(initHP), m_Time(0), m_LastDamageTime(0), m_RecoveryTime(recoveryTime)
{
}

std::string HealthComponent::getTypeName() const
{
	return "Health";
}

std::list<Property> HealthComponent::listProperties() const
{
	std::list<Property> props;
	Property pr;

	pr.setName("Max. health");
	pr.setFloat(m_MaxHP);
	pr.setAsMutable(true);
	props.push_back(pr);

	pr.reset();
	pr.setName("Recovery time");
	pr.setFloat(m_RecoveryTime);
	pr.setAsMutable(true);
	props.push_back(pr);

	return props;
}

void HealthComponent::initialise(Entity* owner)
{
	m_Owner=owner;
}

void HealthComponent::update(float dt)
{
	m_Time+=dt;
	if(m_Time - m_LastDamageTime >= m_RecoveryTime)
	{
		m_HP+=std::ceil((float)m_MaxHP*0.1f);
		if(m_HP > m_MaxHP)
			m_HP=m_MaxHP;
	}
}

void HealthComponent::onDamage(Entity* other, int damage)
{
	if(m_HP > 0 && m_HP-damage <= 0)
		m_Owner->onGenericEvent("Death");

	m_LastDamageTime=m_Time;

	m_HP-=damage;
	if(m_HP < 0)
		m_HP=0;
}