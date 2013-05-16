#ifndef _CAMERACOMPONENT_HPP_
#define _CAMERACOMPONENT_HPP_

#include "../Entity.hpp"
#include "TransformableComponent.hpp"
#include "../../3rdParty/rapidxml-1.13/rapidxml.hpp"
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

    static IComponent* factoryFunction(rapidxml::xml_node<>* data);

private:
	TransformableComponent* m_Transform;
	b2Vec2 m_Size;
	sf::View m_View;

	static CameraComponent* ms_Active;
};

#endif /* _CAMERACOMPONENT_HPP_ */
