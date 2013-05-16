#ifndef _PLAYERCTRLCOMPONENT_HPP_
#define _PLAYERCTRLCOMPONENT_HPP_

#include "../Entity.hpp"
#include "PhysicsComponent.hpp"
#include "TransformableComponent.hpp"
#include "WeaponComponent.hpp"

class PlayerCtrlComponent : public IComponent
{
public:
	PlayerCtrlComponent();

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void initialise(Entity* owner);
	void update(float dt);

	static IComponent* factoryFunction(rapidxml::xml_node<>* comp_data);

private:
	Entity* m_Owner;
	PhysicsComponent* m_Physics;
	TransformableComponent* m_Transform;
    WeaponComponent* m_Weapon;
};

#endif /* _PLAYERCTRLCOMPONENT_HPP_ */
