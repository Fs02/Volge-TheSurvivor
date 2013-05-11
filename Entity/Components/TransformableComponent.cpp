#include "TransformableComponent.hpp"

TransformableComponent::TransformableComponent()
	:m_HasChanged(false), m_Position(0, 0), m_Rotation(0)
{
}

void TransformableComponent::setPosition(const b2Vec2& pos)
{
	m_Position=pos;
	m_HasChanged=true;
}

const b2Vec2& TransformableComponent::position() const
{
	return m_Position;
}

void TransformableComponent::setRotation(float rot)
{
	m_Rotation=rot;
	m_HasChanged=true;
}

float TransformableComponent::rotation() const
{
	return m_Rotation;
}

bool TransformableComponent::hasChanged() const
{
	return m_HasChanged;
}

void TransformableComponent::initialise(Entity* owner)
{
}

void TransformableComponent::update(float dt)
{
}
