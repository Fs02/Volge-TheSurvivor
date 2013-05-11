#ifndef _PHYSICSCOMPONENT_HPP_
#define _PHYSICSCOMPONENT_HPP_

#include "../Entity.hpp"
#include "TransformableComponent.hpp"
#include "../../MadEngine/Interface/IPhysicsSystem.hpp"

namespace PhysicsShape
{
	enum Enum
	{
		Circle, Box
	};
}

/*
 * To get a static body, set mass to zero, or a negative number
 */
struct PhysicsDef
{
	PhysicsShape::Enum shape;
	float friction;
	float mass;

	struct
	{
		float radius;
	} circle;
	struct
	{
		b2Vec2 size;
	} box;

	PhysicsDef();

	float surface() const;
};

class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent(Mad::Interface::IPhysicsSystem* physics, const PhysicsDef& def, int categoryBits);
	~PhysicsComponent();

	void setSpeed(const b2Vec2& speed);

	void initialise(Entity* owner);
	void update(float dt);

private:
	Mad::Interface::IPhysicsSystem* m_Physics;
	TransformableComponent* m_Transform;
	b2Body* m_Body;
};

#endif /* _PHYSICSCOMPONENT_HPP_ */
