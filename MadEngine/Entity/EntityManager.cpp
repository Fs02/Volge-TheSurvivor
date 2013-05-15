#include "EntityManager.hpp"
#include <iostream>
#include "Components/CameraComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/PlayerCtrlComponent.hpp"
#include "Components/SoundComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformableComponent.hpp"
#include "Components/WeaponComponent.hpp"

EntityManager::EntityManager(PhysicsSystem *pm)
{
	m_PhysicsManager = pm;
	m_Listener	= nullptr;
}

EntityManager::~EntityManager()
{
}

void EntityManager::setListener(IEntityMgrListener *listener)
{
    m_Listener=listener;
}

Entity *EntityManager::createEntity(const std::string& name)
{
    if(m_Entities.count(name) == 1)
        return nullptr;
    Entity* ent=new Entity();
	    m_Entities[name]=ent;
    if(m_Listener != nullptr)
       m_Listener->onEntityAdded(name, ent);
    return ent;
}

Entity* EntityManager::getEntity(const std::string &name)
{
    auto iter=m_Entities.find(name);
    if(iter == m_Entities.end())
        return nullptr;
    return iter->second;
}

const Entity* EntityManager::getEntity(const std::string &name) const
{
    auto iter=m_Entities.find(name);
    if(iter == m_Entities.end())
        return nullptr;
    return iter->second;
}

std::list<std::string> EntityManager::listEntities() const
{
    std::list<std::string> result;
    for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
        result.push_back(iter->first);
    return result;
}

void EntityManager::update(float deltaTime)
{
	for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
	{
		iter->second->update(deltaTime);
		if(iter->second->isRedundant())	
			m_Redundant.push_back(iter->second);
	}

	while(!m_Redundant.empty())
	{
		this->m_removeEntity(m_Redundant.front());
		m_Redundant.pop_front();
	}
}

void EntityManager::m_removeEntity(Entity *ent)
{
    for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
    {
        if(iter->second == ent)
        {
            if(m_Listener)
                m_Listener->onEntityRemoved(iter->first, ent);
            m_Entities.erase(iter);
            delete ent;
            return;
        }
    }
}