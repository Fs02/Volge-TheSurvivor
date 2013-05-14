#include "stdafx.h"
#include "CameraComponent.hpp"

CameraComponent* CameraComponent::ms_Active=nullptr;

CameraComponent::CameraComponent()
	:m_Transform(nullptr)
{
	this->setVirtualSize(b2Vec2(10, 10));
}

CameraComponent::~CameraComponent()
{
	if(ms_Active == this)
		ms_Active=nullptr;
}

void CameraComponent::makeActive()
{
	ms_Active=this;
}

void CameraComponent::setVirtualSize(const b2Vec2& size)
{
	m_Size=size;
}

std::string CameraComponent::getTypeName() const
{
	return "Camera";
}

std::list<Property> CameraComponent::listProperties() const
{
	std::list<Property> props;
	Property pr;

	pr.setName("Size");
	pr.setVec2(m_Size);
	pr.setAsMutable(true);
	props.push_back(pr);

	pr.reset();
	pr.setName("Is active");
	pr.setBool((ms_Active == this));
	pr.setAsMutable(true);
	props.push_back(pr);

	return props;
}

void CameraComponent::initialise(Entity* owner)
{
	m_Transform=owner->component<TransformableComponent>();
}

void CameraComponent::update(float dt)
{
	if(ms_Active == this && m_Transform)
	{
		b2Vec2 pos=m_Transform->position();
		m_View.setCenter(pos.x, pos.y);
		m_Size.x=m_Size.y*Mad::Manager::Graphics::getSingleton()->getAspectRatio();
		m_View.setSize(m_Size.x, m_Size.y);
		Mad::Manager::Graphics::getSingleton()->setGameView(m_View);
	}
}
