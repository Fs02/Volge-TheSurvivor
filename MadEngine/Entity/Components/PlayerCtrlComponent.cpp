#include "stdafx.h"
#include "PlayerCtrlComponent.hpp"
#include "Manager/Controller.hpp"

PlayerCtrlComponent::PlayerCtrlComponent()
	:m_Owner(nullptr), m_Physics(nullptr), m_Transform(nullptr)
{
}

std::string PlayerCtrlComponent::getTypeName() const
{
	return "Player controller";
}

std::list<Property> PlayerCtrlComponent::listProperties() const
{
	return std::list<Property>();
}

void PlayerCtrlComponent::initialise(Entity* owner)
{
	m_Owner=owner;
	m_Physics=owner->component<PhysicsComponent>();
	m_Transform=owner->component<TransformableComponent>();
}

void PlayerCtrlComponent::update(float dt)
{
	if(!m_Physics || !m_Transform)
		return;

	auto ctrl=Mad::Manager::Controller::getSingleton();

	b2Vec2 fwd;
	fwd.x=std::cos(m_Transform->rotation());
	fwd.y=std::sin(m_Transform->rotation());

	b2Vec2 dir(0, 0);
	float angle=m_Transform->rotation();

	int ydir=0;

	if(ctrl->getControl("forward"))
		ydir-=1;
	if(ctrl->getControl("backward"))
		ydir+=1;

	dir.Set(0, ydir);

	switch(ydir)
	{
	case -1:
		m_Owner->onStateChanged("Walk forward");
		break;
	case 1:
		m_Owner->onStateChanged("Walk backward");
		break;
	default:
		m_Owner->onStateChanged(CommonStates::Idle);
		break;
	}

	//SFML have inverted y axis, the same applies with angle
	if(ctrl->getControl("left"))
		angle-=10.0f*b2_pi/180.0f;
	if(ctrl->getControl("right"))
		angle+=10.0f*b2_pi/180.0f;

	m_Physics->setSpeed(1.5f);
	m_Physics->setMovementDirection(dir);
	m_Physics->setAngle(angle);
}
