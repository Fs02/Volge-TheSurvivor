#pragma once

#include "../../stdafx.h"
#include "../Entity.hpp"

// rotation is given in degrees!
class TransformableComponent : public IComponent
{
public:
	TransformableComponent();

	void setPosition(const sf::Vector2f& pos);
	const sf::Vector2f& position() const;
	void setRotation(float rot);
	float rotation() const;

	void initialise(Entity* owner);
	void update(float dt);

private:
	sf::Vector2f m_Position;
	float m_Rotation;
};
