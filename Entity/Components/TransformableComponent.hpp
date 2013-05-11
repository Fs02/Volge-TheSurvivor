#pragma once

#include "../../stdafx.h"
#include "../Entity.hpp"

/*
 * This class allows to change b2Body's position
 * (if there is PhysicsComponent in the object),
 * but changing it may cause bugs. Use it wisely!
 */
class TransformableComponent : public IComponent
{
	friend class PhysicsComponent;

public:
	TransformableComponent();

	void setPosition(const b2Vec2& pos);
	const b2Vec2& position() const;
	void setRotation(float rot);
	float rotation() const;

	void initialise(Entity* owner);
	void update(float dt);

private:
	bool m_HasChanged;
	b2Vec2 m_Position;
	float m_Rotation;
};
