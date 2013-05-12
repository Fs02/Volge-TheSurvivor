#pragma once

#include "TransformableComponent.hpp"
#include "../../MadEngine/Graphics/Sprite.hpp"

class SpriteComponent : public IComponent
{
public:
	SpriteComponent();
	~SpriteComponent();

	void setSprite(const std::string& name);

	void initialise(Entity* owner);
	void update(float dt);

private:
	TransformableComponent* m_Transformable;
	Mad::Graphics::Sprite* m_Sprite;
};
