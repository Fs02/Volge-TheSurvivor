#pragma once

#include "../stdafx.h"

class IComponent;

class Entity
{
public:
	Entity();
	~Entity();

	void initialise();
	void addComponent(IComponent* comp);
	template<class T>
	inline T* component();
	template<class T>
	inline const T* component() const;

	void update(float deltaTime);
	void onCollisionBegin(Entity* other);
	void onCollisionEnd(Entity* other);
	void onDamage(Entity* other, int damage);
	void onGenericEvent(const std::string& name);

private:
	std::vector<IComponent*> m_components;

	Entity(const Entity&);
};

class IComponent
{
public:
	virtual ~IComponent();

	virtual void initialise(Entity* owner)=0;

	virtual void update(float deltaTime)=0;
	virtual void onCollisionBegin(Entity* other);
	virtual void onCollisionEnd(Entity* other);
	virtual void onDamage(Entity* other, int damage);
	virtual void onGenericEvent(const std::string& name);
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
