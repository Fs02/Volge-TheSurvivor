#include "Entity.hpp"

/*
 * CommonStates
 */

const std::string CommonStates::Idle="Idle";
const std::string CommonStates::Dead="Dead";

/*
 * Entity
 */

Entity::Entity()
	:m_IsRedundant(false)
{
}

Entity::~Entity()
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		delete m_components[i];
}

void Entity::initialise()
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->initialise(this);
}

void Entity::addComponent(IComponent* comp)
{
	if(!comp)
		return;
	for(unsigned int i=0; i < m_components.size(); ++i)
		if(m_components[i] == comp)
			return;
	m_components.push_back(comp);
}

std::list<const IComponent*> Entity::listComponents() const
{
	std::list<const IComponent*> result;
	for(size_t i=0; i < m_components.size(); ++i)
		result.push_back(m_components[i]);
	return result;
}

void Entity::update(float deltaTime)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->update(deltaTime);
}

void Entity::onCollisionBegin(Entity* other)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onCollisionBegin(other);
}

void Entity::onCollisionEnd(Entity* other)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onCollisionEnd(other);
}

void Entity::onDamage(Entity* other, int damage)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onDamage(other, damage);
}

void Entity::onStateChanged(const std::string& stateName)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onStateChanged(stateName);
}

void Entity::onGenericEvent(const std::string& name)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onGenericEvent(name);
}

void Entity::markAsRedundant()
{
	m_IsRedundant=true;
}

bool Entity::isRedundant() const
{
	return m_IsRedundant;
}

/*
 * IComponent
 */

IComponent::~IComponent()
{
}

void IComponent::onCollisionBegin(Entity* other)
{
}

void IComponent::onCollisionEnd(Entity* other)
{
}

void IComponent::onDamage(Entity* other, int damage)
{
}

void IComponent::onStateChanged(const std::string& stateName)
{
}

void IComponent::onGenericEvent(const std::string& name)
{
}
