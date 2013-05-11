#include "stdafx.h"
#include "PhysicsComponent.hpp"

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
	:m_Physics(physics), m_Transform(nullptr), m_Body(nullptr)
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

void PhysicsComponent::applyVelocity(const b2Vec2& appVel)
{
	b2Vec2 vel=m_Body->GetLinearVelocity();
	vel+=appVel;
	m_Body->SetLinearVelocity(vel);
}

void PhysicsComponent::initialise(Entity* owner)
{
	m_Transform=owner->component<TransformableComponent>();
	m_Body->SetUserData((void*)owner);
	m_Body->SetTransform(m_Transform->position(), m_Transform->rotation());
}

void PhysicsComponent::update(float dt)
{
	if(!m_Transform)
		return;

	if(m_Transform->hasChanged())
	{
		m_Body->SetTransform(m_Transform->position(), m_Transform->rotation());
		m_Transform->m_HasChanged=false;
	}

	const b2Transform& tr=m_Body->GetTransform();
	m_Transform->m_Position=tr.p;
	m_Transform->m_Rotation=tr.q.GetAngle();
}
