#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int maxHP, int initHP, float recoveryTime)
		: m_Owner(nullptr), m_MaxHP(maxHP), m_HP(initHP), m_Time(0), m_LastDamageTime(
				0), m_RecoveryTime(recoveryTime), m_DeathTime(0)
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
	m_Owner = owner;
}

void HealthComponent::update(float dt)
{
	m_Time += dt;
	if (this->isAlive() && m_Time - m_LastDamageTime >= m_RecoveryTime)
	{
		m_HP += std::ceil((float) m_MaxHP * 0.1f);
		if (m_HP > m_MaxHP)
			m_HP = m_MaxHP;
	} else if (!this->isAlive() && m_Time - m_DeathTime >= 30.0f)
		m_Owner->markAsRedundant();
}

void HealthComponent::onDamage(Entity* other, int damage)
{
	if (m_HP > 0 && m_HP - damage <= 0)
		m_Owner->onStateChanged(CommonStates::Dead);

	m_LastDamageTime = m_Time;

	m_HP -= damage;
	if (m_HP < 0)
		m_HP = 0;
}

void HealthComponent::onStateChanged(const std::string& stateName)
{
	if (stateName == CommonStates::Idle)
	{
		m_DeathTime = m_Time;
	}
}

bool HealthComponent::isAlive() const
{
	return (m_HP > 0);
}

IComponent* HealthComponent::factoryFunction(rapidxml::xml_node<>* comp_data)
{
	int maxHealth, initHealth;
	float recoveryTime;
	for (comp_data; comp_data; comp_data = comp_data->next_sibling())
	{
		std::string name = comp_data->first_attribute("name")->value();
		if (name == "maxHP")
			maxHealth = std::stoi(comp_data->first_attribute("value")->value());
		else if (name == "initHP")
			initHealth = std::stoi(comp_data->first_attribute("value")->value());
		else if (name == "recoveryTime")
			recoveryTime = std::stof(comp_data->first_attribute("value")->value());
		else;
	}
	return new HealthComponent(maxHealth, initHealth, recoveryTime);
}