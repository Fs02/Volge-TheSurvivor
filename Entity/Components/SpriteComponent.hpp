#pragma once

#include "TransformableComponent.hpp"
#include "../../MadEngine/Graphics/AniSprite.hpp"

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
	Mad::Graphics::AniSprite* m_Sprite;
};
