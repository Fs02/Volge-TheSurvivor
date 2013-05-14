#pragma once
#include "Entity.hpp"
#include "../MadEngine/MadEngine.hpp"
#include <map>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

    Entity* createEntity(const std::string& name);
    Entity* getEntity(const std::string& name);
    const Entity* getEntity(const std::string &name) const;
    std::list<std::string> listEntities() const;

	void update(float deltaTime);

private:
    std::map<std::string, Entity*> m_Entities;
};
