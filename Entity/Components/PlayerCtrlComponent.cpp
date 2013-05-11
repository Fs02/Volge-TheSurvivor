#include "PlayerCtrlComponent.hpp"
#include "../../MadEngine/Manager/Controller.hpp"

PlayerCtrlComponent::PlayerCtrlComponent()
	:m_Physics(nullptr), m_Transform(nullptr)
{
}

void PlayerCtrlComponent::initialise(Entity* owner)
{
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

	if(ctrl->getControl("forward"))
		dir+=b2Vec2(0, 1);
	if(ctrl->getControl("backward"))
		dir+=b2Vec2(0, -1);

	if(ctrl->getControl("left"))
		angle+=180.0f*dt*b2_pi/180.0f;
	if(ctrl->getControl("right"))
		angle-=180.0f*dt*b2_pi/180.0f;

	m_Physics->setSpeed(20);
	m_Physics->setMovementDirection(dir);
	m_Physics->setAngle(angle);
}
