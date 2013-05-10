#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int maxHP, int initHP, float recoveryTime)
	:m_Owner(nullptr), m_MaxHP(maxHP), m_HP(initHP), m_Time(0), m_LastDamageTime(0), m_RecoveryTime(recoveryTime)
{
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
