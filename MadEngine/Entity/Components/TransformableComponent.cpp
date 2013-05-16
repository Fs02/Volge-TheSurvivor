#include "TransformableComponent.hpp"

TransformableComponent::TransformableComponent()
	:m_HasChanged(false), m_Position(0, 0), m_Rotation(0)
{
}

std::string TransformableComponent::getTypeName() const
{
	return "Transformable";
}

std::list<Property> TransformableComponent::listProperties() const
{
	std::list<Property> props;
	Property pr;

	pr.setName("Position");
	pr.setVec2(m_Position);
	pr.setAsMutable(true);
	props.push_back(pr);

	pr.reset();
	pr.setName("Rotation");
	pr.setFloat(m_Rotation);
	pr.setAsMutable(true);
	props.push_back(pr);

	return props;
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

void TransformableComponent::initialise(Entity* owner)
{
}

void TransformableComponent::update(float dt)
{
}

IComponent* TransformableComponent::factoryFunction(rapidxml::xml_node<>* comp_data)
{
	TransformableComponent* tc = new TransformableComponent();
	for (comp_data; comp_data; comp_data = comp_data->next_sibling())
	{
		std::string name = comp_data->first_attribute("name")->value();
		if (name == "default-pos")
			tc->setPosition(b2Vec2(std::stof(comp_data->first_attribute("pos-x")->value()), std::stof(comp_data->first_attribute("pos-y")->value())));
		else if(name == "default-rot")
			tc->setRotation(std::stof(comp_data->first_attribute("rot")->value()) * b2_pi / 180.f);
		else;
	}
	return tc;
}