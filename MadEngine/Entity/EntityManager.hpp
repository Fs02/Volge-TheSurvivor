#pragma once
#include "Entity.hpp"
#include "../MadEngine/MadEngine.hpp"
#include <map>
#include <list>

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
	EntityManager();
	~EntityManager();

    void setListener(IEntityMgrListener* listener);

    Entity* createEntity(const std::string& name);
    Entity* getEntity(const std::string& name);
    const Entity* getEntity(const std::string &name) const;
    std::list<std::string> listEntities() const;

	void update(float deltaTime);

private:
    IEntityMgrListener* m_Listener;
    std::map<std::string, Entity*> m_Entities;
    std::list<Entity*> m_Redundant;

    void m_removeEntity(Entity* ent);
};
