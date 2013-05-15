#pragma once
#include "Entity.hpp"
#include <map>
#include <list>
#include <fstream>
#include "PhysicsSystem.hpp"
#include "../3rdParty/rapidxml-1.13/rapidxml.hpp"

class IEntityMgrListener
{
public:
    virtual ~IEntityMgrListener(){}

    virtual void onEntityAdded(const std::string& name, Entity* ent)=0;
    virtual void onEntityRemoved(const std::string& name, Entity* ent)=0;
};

class EntityManager
{
public:
	EntityManager(PhysicsSystem *pm);
	~EntityManager();

    void setListener(IEntityMgrListener* listener);

    Entity* createEntity(const std::string& name);
    Entity* getEntity(const std::string& name);

//	void loadEntity(const std::string& fileName);
//	void createEntity(Entity* ent);
//	void destroyEntity(Entity* ent);

    const Entity* getEntity(const std::string &name) const;
    std::list<std::string> listEntities() const;

	void update(float deltaTime);
	//Execute entity creation
//	void preLoop();
	//Execute entity deletion
//	void postLoop();

private:
    IEntityMgrListener* m_Listener;
	std::map<std::string, Entity*> m_Entities;
//	std::vector<Entity*> m_Entities;
//  std::list<Entity*> m_TobeAdded;
//	std::list<Entity*> m_TobeRemoved;
	std::list<Entity*> m_Redundant;
	PhysicsSystem* m_PhysicsManager;
    void m_removeEntity(Entity* ent);
};
