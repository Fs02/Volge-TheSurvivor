#include "stdafx.h"
#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

Entity *EntityManager::createEntity(const std::string& fileName)
{
}

void EntityManager::addEntity(Entity* entity)
{
	m_Entities.push_back(entity);
}

void EntityManager::destroyEntity(Entity* entity)
{
	m_Entities.erase(std::find(m_Entities.begin(), m_Entities.end(), entity));
	delete entity;
}

void EntityManager::update(float deltaTime)
{
	for (auto it = m_Entities.begin(); it != m_Entities.end(); )
	{
		if (*it)
		{
			(*it)->update(deltaTime);
			++it;
		}
		else
		{
			it = m_Entities.erase(it);
		}
	}
}