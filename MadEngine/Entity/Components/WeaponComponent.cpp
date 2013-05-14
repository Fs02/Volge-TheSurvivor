#include "WeaponComponent.hpp"
#include "../../Manager/Controller.hpp"
#include <iostream>

WeaponComponent::WeaponComponent(PhysicsSystem* physics)
	:m_Physics(physics), m_Owner(nullptr), m_Gun(nullptr), m_Transform(nullptr)
{
}

WeaponComponent::~WeaponComponent()
{
	delete m_Gun;
}

std::string WeaponComponent::getTypeName() const
{
	return "Weapon";
}

std::list<Property> WeaponComponent::listProperties() const
{
	return std::list<Property>();
}

void WeaponComponent::setGun(Item::Gun* gun)
{
	delete m_Gun;
	m_Gun=gun;
}

void WeaponComponent::initialise(Entity* ent)
{
	m_Owner=ent;
	m_Transform=ent->component<TransformableComponent>();
}

void WeaponComponent::update(float dt)
{
	if(!m_Transform || !m_Gun)
		return;

	m_Gun->update(dt);

	auto ctrl=Mad::Manager::Controller::getSingleton();

	float angle=m_Transform->rotation()-b2_pi/2.0f;
	b2Vec2 dir(std::cos(angle), std::sin(angle));
	dir*=100.0f;	// 100 is the maximum range of the gun
	b2Vec2 origin=m_Transform->position();
	b2Vec2 end=origin;
	end+=dir;

//	Mad::Utility::DrawBatch& db=Mad::Manager::Graphics::getSingleton()->getDrawBatch();
//	db.drawLine(origin, end, sf::Color(255, 0, 0));

	if(ctrl->getControl("attack") && m_Gun->shoot())
	{
		std::cout<<"Shooting a bullet!\n";
		Entity* ent=m_Physics->rayCast(origin, end);
		if(ent)
			ent->onDamage(m_Owner, m_Gun->getBulletDamage());

		if(ent == m_Owner)
			std::cout<<"Fuck, I've shoot myself!\n";
	}
}
