#pragma once
#include "Entity.hpp"
#include "../MadEngine/MadEngine.hpp"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* createEntity(const std::string& fileName);
	void addEntity(Entity* entity);
	void destroyEntity(Entity* entity);
	void update(float deltaTime);

private:
	std::vector<Entity*> m_Entities;
};
