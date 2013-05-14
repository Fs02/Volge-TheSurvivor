#ifndef _CAMERACOMPONENT_HPP_
#define _CAMERACOMPONENT_HPP_

#include "../Entity.hpp"
#include "TransformableComponent.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class CameraComponent : public IComponent
{
public:
	CameraComponent();
	~CameraComponent();

	void makeActive();
	void setVirtualSize(const b2Vec2& size);

	std::string getTypeName() const;
	std::list<Property> listProperties() const;

	void initialise(Entity* owner);
	void update(float dt);

private:
	TransformableComponent* m_Transform;
	b2Vec2 m_Size;
	sf::View m_View;

	static CameraComponent* ms_Active;
};

#endif /* _CAMERACOMPONENT_HPP_ */
