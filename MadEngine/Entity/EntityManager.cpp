#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

Entity *EntityManager::createEntity(const std::string& name)
{
    Entity* ent=new Entity();
    m_Entities[name]=ent;
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
        iter->second->update(deltaTime);
}
