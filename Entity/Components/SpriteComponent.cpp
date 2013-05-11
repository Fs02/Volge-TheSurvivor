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
	Mad::Graphics::AniSprite* as=new Mad::Graphics::AniSprite();
	as->setTexture(name);
	as->setFrameSize(128, 128);
	as->setLoopSpeed(10);
	as->setOrigin(64, 80);
	as->setInvertSprite(true);
	as->play();
	m_Sprite=as;
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
	m_Sprite->setPosition(pos.x, pos.y);
	m_Sprite->setRotation(rot*180.0f/b2_pi);
	m_Sprite->update(dt);
	m_Sprite->draw();
}