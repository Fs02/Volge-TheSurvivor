#pragma once

#include "../Entity.hpp"

class HealthComponent : public IComponent
{
public:
	HealthComponent(int maxHP, int initHP, float recoveryTime);

	void initialise(Entity* owner);
	void update(float dt);
	void onDamage(Entity* other, int damage);

private:
	Entity* m_Owner;
	int m_MaxHP, m_HP;
	float m_Time, m_LastDamageTime, m_RecoveryTime;
};
