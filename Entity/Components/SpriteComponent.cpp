#include "stdafx.h"
#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent()
	:m_Transformable(nullptr), m_Sprite(nullptr)
{
}

SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

void SpriteComponent::setSprite(const std::string& name)
{
	delete m_Sprite;
	m_Sprite=new Mad::Graphics::Sprite(name);
}

void SpriteComponent::initialise(Entity* owner)
{
	m_Transformable=owner->component<TransformableComponent>();
}

void SpriteComponent::update(float dt)
{
	if(!m_Transformable)
		return;

	b2Vec2 pos=m_Transformable->position();
	float rot=m_Transformable->rotation();
	m_Sprite->setPosition(pos);
	m_Sprite->setRotation(rot);
	m_Sprite->draw(dt);
}
