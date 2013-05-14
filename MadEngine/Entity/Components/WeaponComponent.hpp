#ifndef _WEAPONCOMPONENT_HPP_
#define _WEAPONCOMPONENT_HPP_

#include "../Entity.hpp"
#include "TransformableComponent.hpp"
#include "../Item/Gun.hpp"
#include "../PhysicsSystem.hpp"

class WeaponComponent : public IComponent
{
public:
	WeaponComponent(PhysicsSystem* physics);
	~WeaponComponent();

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void setGun(Item::Gun* gun);

	void initialise(Entity* ent);
	void update(float dt);

private:
	PhysicsSystem* m_Physics;
	Entity* m_Owner;
	Item::Gun* m_Gun;
	TransformableComponent* m_Transform;
};

#endif /* _WEAPONCOMPONENT_HPP_ */
