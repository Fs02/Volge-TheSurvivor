#pragma once

#include "../../stdafx.h"
#include "../Entity.hpp"

// rotation is given in degrees!
class TransformableComponent : public IComponent
{
public:
	TransformableComponent();

	void setPosition(const b2Vec2& pos);
	const b2Vec2& position() const;
	void setRotation(float rot);
	float rotation() const;

	void initialise(Entity* owner);
	void update(float dt);

private:
	b2Vec2 m_Position;
	float m_Rotation;
};
