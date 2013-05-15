#ifndef _PLAYERCTRLCOMPONENT_HPP_
#define _PLAYERCTRLCOMPONENT_HPP_

#include "../Entity.hpp"
#include "PhysicsComponent.hpp"
#include "TransformableComponent.hpp"

class PlayerCtrlComponent : public IComponent
{
public:
	PlayerCtrlComponent();

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void initialise(Entity* owner);
	void update(float dt);

private:
	Entity* m_Owner;
	PhysicsComponent* m_Physics;
	TransformableComponent* m_Transform;
};

#endif /* _PLAYERCTRLCOMPONENT_HPP_ */
