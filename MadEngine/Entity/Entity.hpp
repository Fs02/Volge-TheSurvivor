#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "Property.hpp"
#include <list>
#include <vector>
#include <map>
#include "../3rdParty/rapidxml-1.13/rapidxml.hpp"

class IComponent;
class ComponentFactory;
typedef IComponent* (*FactoryFunc) ();

namespace CommonStates
{
	extern const std::string Idle;
	extern const std::string Dead;
}

class Entity
{
public:
	Entity();
	~Entity();

	void initialise();
	void addComponent(IComponent* comp);
	void removeComponent(IComponent* comp);
	template<class T>
	inline T* component();
	template<class T>
	inline const T* component() const;
    std::list<IComponent*> listComponents() const;

	void loadComponent(const std::string& fileName);
	void update(float deltaTime);
	void onCollisionBegin(Entity* other);
	void onCollisionEnd(Entity* other);
	void onDamage(Entity* other, int damage);
	void onStateChanged(const std::string& stateName);
	void onGenericEvent(const std::string& name);

	void markAsRedundant();
	bool isRedundant() const;

private:
	bool m_IsRedundant;
	std::vector<IComponent*> m_components;

	Entity(const Entity&);
};

class IComponent
{
public:
	virtual ~IComponent();

	virtual std::string getTypeName() const=0;
	virtual std::list<Property> listProperties() const=0;

	virtual void initialise(Entity* owner)=0;

	virtual void update(float deltaTime)=0;
	virtual void onCollisionBegin(Entity* other);
	virtual void onCollisionEnd(Entity* other);
	virtual void onDamage(Entity* other, int damage);
	virtual void onStateChanged(const std::string& stateName);
	virtual void onGenericEvent(const std::string& name);
	virtual void onDetailChanged(int detail)
	{}
	virtual void ConstructComponent()
	{}
};

class ComponentFactory
{
private:
	ComponentFactory();
	~ComponentFactory();

	static ComponentFactory* instance;
	std::map<std::string, FactoryFunc> m_FactoryFuncs;

public:
	static ComponentFactory* getSingleton();
	void addFactoryFunction(const std::string& compType, FactoryFunc func);
	FactoryFunc getFactoryFunction(const std::string& compType);
};

/*
 * Implementation
 */

template<class T>
inline T* Entity::component()
{
	T* ptr;
	for(unsigned int i=0; i < m_components.size(); ++i)
	{
		if((ptr=dynamic_cast<T*>(m_components[i])) != nullptr)
			return ptr;
	}
	return nullptr;
}

template<class T>
inline const T* Entity::component() const
{
	const T* ptr;
	for(unsigned int i=0; i < m_components.size(); ++i)
	{
		if((ptr=dynamic_cast<const T*>(m_components[i])) != nullptr)
			return ptr;
	}
	return nullptr;
}

#endif
