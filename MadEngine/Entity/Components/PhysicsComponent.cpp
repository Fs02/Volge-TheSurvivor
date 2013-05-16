#include "PhysicsComponent.hpp"
#include "../PhysicsSystem.hpp"

/*
 * PhysicsDef
 */

PhysicsDef::PhysicsDef()
	:shape(PhysicsShape::Circle), friction(0), mass(0)
{
	circle.radius=0;
	box.size.Set(0, 0);
}

float PhysicsDef::surface() const
{
	switch(shape)
	{
	case PhysicsShape::Circle:
		return b2_pi*std::pow(circle.radius, 2);
	case PhysicsShape::Box:
		return box.size.x*box.size.y;
	}

	return 0;
}

/*
 * PhysicsComponent
 */

PhysicsComponent::PhysicsComponent(Mad::Interface::IPhysicsSystem* physics,
		const PhysicsDef& def, int categoryBits)
	:m_Physics(physics), m_Transform(nullptr), m_Body(nullptr), m_Speed(0), m_Angle(0), m_Direction(0, 0)
{
	float surf=def.surface();
	float dens=0;
	if(surf > 0)
		dens=def.mass/surf;

	b2FixtureDef fixDef;
	fixDef.density=dens;
	fixDef.filter.categoryBits=categoryBits;
	fixDef.friction=def.friction;

	switch(def.shape)
	{
	case PhysicsShape::Circle:
		{
			auto sh=new b2CircleShape();
			sh->m_radius=def.circle.radius;
			fixDef.shape=sh;
		}break;
	case PhysicsShape::Box:
		{
			auto sh=new b2PolygonShape();
			sh->SetAsBox(def.box.size.x/2.0f, def.box.size.y/2.0f);
			fixDef.shape=sh;
		}break;
	}

	b2BodyDef bodyDef;
	bodyDef.type=(def.mass <= 0 ? b2_staticBody : b2_dynamicBody);
	m_Body=m_Physics->createBody(bodyDef);
	m_Body->CreateFixture(&fixDef);
	delete fixDef.shape;
}

PhysicsComponent::~PhysicsComponent()
{
	m_Physics->destroyBody(m_Body);
}

std::string PhysicsComponent::getTypeName() const
{
	return "Physics";
}

std::list<Property> PhysicsComponent::listProperties() const
{
	std::list<Property> props;
	Property pr;

	// TODO

	return props;
}

void PhysicsComponent::setSpeed(float speed)
{
	m_Speed=speed;
}

void PhysicsComponent::setMovementDirection(const b2Vec2& dir)
{
	m_Direction=dir;
}

void PhysicsComponent::setAngle(float angle)
{
	m_Angle=angle;
}

void PhysicsComponent::initialise(Entity* owner)
{
	m_Transform=owner->component<TransformableComponent>();
	m_Body->SetUserData((void*)owner);
}

void PhysicsComponent::update(float dt)
{
	if(!m_Transform)
		return;

	if(m_Transform->m_HasChanged)
	{
		m_Body->SetTransform(m_Transform->position(), m_Transform->rotation());
		m_Transform->m_HasChanged=false;
	}

	b2Vec2 dir=m_Body->GetWorldVector(m_Direction);
	m_Body->ApplyLinearImpulse(m_Speed*m_Body->GetMass()*dir, m_Body->GetWorldCenter());
	m_Body->ApplyLinearImpulse(-0.2f*m_Body->GetMass()*m_Body->GetLinearVelocity(), m_Body->GetWorldCenter());
	
	float nextAngle=m_Body->GetAngle() + m_Body->GetAngularVelocity()/ 60;
	float rotation=m_Angle-nextAngle;
	float angVel=rotation*60.0f;
	m_Body->ApplyAngularImpulse(angVel*m_Body->GetInertia());

	m_Transform->m_Position=m_Body->GetPosition();
	m_Transform->m_Rotation=m_Body->GetAngle();
}

IComponent* PhysicsComponent::factoryFunction(rapidxml::xml_node<>* comp_data)
{
	PhysicsDef def;
	int catBits;
	for (comp_data; comp_data; comp_data = comp_data->next_sibling())
	{
		std::string name = comp_data->first_attribute("name")->value();
		if (name == "Shape")
		{
			std::string s = comp_data->first_attribute("value")->value();
			if (s == "Circle")
			{
				def.shape = PhysicsShape::Circle;
				def.circle.radius = std::stof(comp_data->first_attribute("radius")->value());
			} 
			else if (s == "Box")
			{
				def.shape = PhysicsShape::Box;
				def.box.size.Set(std::stof(comp_data->first_attribute("size-x")->value()), std::stof(comp_data->first_attribute("size-y")->value()));
			}
			else;
		}
		else if (name == "Friction")
			def.friction = std::stof(comp_data->first_attribute("value")->value());
		else if (name == "Mass")
			def.mass = std::stof(comp_data->first_attribute("value")->value());
		else if (name == "catBits")
			catBits = std::stoi(comp_data->first_attribute("value")->value());
		else;
	}
	return new PhysicsComponent(PhysicsSystem::getSingleton(), def, catBits);
}