#pragma once

#include "TransformableComponent.hpp"
#include "Graphics/Sprite.hpp"

class SpriteComponent : public IComponent
{
public:
	SpriteComponent();
	~SpriteComponent();

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void setSprite(const std::string& name);
	void setSize(const b2Vec2& size);

	void initialise(Entity* owner);
	void update(float dt);
	void onStateChanged(const std::string& stateName);

private:
	TransformableComponent* m_Transformable;
	Mad::Graphics::Sprite* m_Sprite;
};
