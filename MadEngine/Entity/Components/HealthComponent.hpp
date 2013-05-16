#pragma once

#include "../Entity.hpp"

class HealthComponent : public IComponent
{
public:
	HealthComponent(int maxHP, int initHP, float recoveryTime);

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void initialise(Entity* owner);
	void update(float dt);
	void onDamage(Entity* other, int damage);
	void onStateChanged(const std::string& stateName);

	bool isAlive() const;

	static IComponent* factoryFunction(rapidxml::xml_node<>* comp_data);

private:
	Entity* m_Owner;
	int m_MaxHP, m_HP;
	float m_Time, m_LastDamageTime, m_RecoveryTime, m_DeathTime;
};
