#include "TransformableComponent.hpp"

TransformableComponent::TransformableComponent()
	:m_Rotation(0)
{
}

void TransformableComponent::setPosition(const sf::Vector2f& pos)
{
	m_Position=pos;
}

const sf::Vector2f& TransformableComponent::position() const
{
	return m_Position;
}

void TransformableComponent::setRotation(float rot)
{
	m_Rotation=rot;
}

float TransformableComponent::rotation() const
{
	return m_Rotation;
}

void TransformableComponent::initialise(Entity* owner)
{
}

void TransformableComponent::update(float dt)
{
}
