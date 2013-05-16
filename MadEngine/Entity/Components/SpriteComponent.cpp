#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent()
    :m_Transformable(nullptr)
{
}

SpriteComponent::~SpriteComponent()
{
}

std::string SpriteComponent::getTypeName() const
{
	return "Sprite";
}

std::list<Property> SpriteComponent::listProperties() const
{
	std::list<Property> props;
	Property pr;

	pr.setName("Sprite file");
    if(m_Sprite.getSource())
        pr.setPath(m_Sprite.getSource()->getFileName());
	else
		pr.setPath(std::string());
	pr.setAsMutable(true);
	props.push_back(pr);

	return props;
}

void SpriteComponent::setSprite(const std::string& name)
{
    m_Sprite.setSource(name);
}

void SpriteComponent::setSize(const b2Vec2& size)
{
    m_Sprite.setSize(size);
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
    m_Sprite.setPosition(pos);
    m_Sprite.setRotation(rot);
    m_Sprite.draw(dt);
}

void SpriteComponent::onStateChanged(const std::string& stateName)
{
    m_Sprite.setAnimation(stateName);
}
