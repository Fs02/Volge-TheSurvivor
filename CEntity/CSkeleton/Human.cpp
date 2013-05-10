#include "stdafx.h"
#include "Human.hpp"
#include "../../PhysicsSystem.hpp"

CEntity::CSkeleton::Human::Human(PhysicsSystem* physicsInstance, int catBits)
	: CEntity::ICEntity(physicsInstance)
{
    b2BodyDef def;
    def.type        = b2_dynamicBody;
	def.position.Set(10,10);

    m_Body          = physicsInstance->createBody(def);

    b2PolygonShape shape;
    shape.SetAsBox(0.55f,0.35f);

    b2FixtureDef fixDef;
    fixDef.shape    = &shape;
    fixDef.density  = 1.f;
	fixDef.filter.categoryBits = catBits;
    m_Body->CreateFixture(&fixDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 10.f;
    fixDef.shape    = &circleShape;
    fixDef.isSensor = true;
	fixDef.filter.categoryBits = catBits|CEntity::CENSOR;
    fixDef.density  = 0.f;
    m_Body->CreateFixture(&fixDef);
    m_Body->SetUserData(this);

	m_Speed			= 1.f;
}

CEntity::CSkeleton::Human::~Human()
{
}

void CEntity::CSkeleton::Human::updateFriction()
{
    m_Body->ApplyForce(-2 * m_Body->GetLinearVelocity(), m_Body->GetWorldCenter());
    m_Body->ApplyTorque( m_Body->GetInertia() * -m_Body->GetAngularVelocity());
}

void CEntity::CSkeleton::Human::update(float deltaTime)
{
    b2Vec2 desiredVelocity;
    b2Vec2 vel = m_Body->GetLinearVelocity();

	b2Vec2 direction	= m_Body->GetWorldVector(b2Vec2(0,0));
    float desiredAngle	= m_Body->GetAngle();

	if (0 != (m_State & STATE::FORWARD))		direction		= m_Body->GetWorldVector(b2Vec2(0,1.f));
	else if (0 != (m_State & STATE::BACKWARD))	direction		= m_Body->GetWorldVector(b2Vec2(0,-1.f));
	else;
	if (0 != (m_State & STATE::LEFT))			desiredAngle	+= -5.f * DEGTORAD;
	else if (0 != (m_State & STATE::RIGHT))		desiredAngle	+= 5.f * DEGTORAD;
	else;

    m_Body->ApplyLinearImpulse(m_Speed * direction , m_Body->GetWorldCenter());
    m_Body->ApplyLinearImpulse(-0.2f * m_Body->GetMass() * m_Body->GetLinearVelocity(), m_Body->GetWorldCenter());


    float nextAngle = m_Body->GetAngle() + m_Body->GetAngularVelocity()/ 60;
    float totalRotation = desiredAngle - nextAngle;
    while (totalRotation < -180 * DEGTORAD) totalRotation+=360 * DEGTORAD;
    while (totalRotation > 180 * DEGTORAD)  totalRotation-=360 * DEGTORAD;
    float desiredAngularVelocity = totalRotation * 60;
    m_Body->ApplyAngularImpulse(m_Body->GetInertia() * desiredAngularVelocity);

	updateFriction();
}

void CEntity::CSkeleton::Human::onCollisionBegin(Entity::IEntity* other)
{
}

void CEntity::CSkeleton::Human::onCollisionEnd(Entity::IEntity* other)
{
}

void CEntity::CSkeleton::Human::setSpeed(float speed)
{
	m_Speed				= speed;
}

void CEntity::CSkeleton::Human::setParams(int state)
{
	m_State				= state;
}

const b2Vec2& CEntity::CSkeleton::Human::getPosition()
{
	return m_Body->GetPosition();
}

b2Vec2 CEntity::CSkeleton::Human::getNormal()
{
	return m_Body->GetWorldVector(b2Vec2(0,1));
}

float CEntity::CSkeleton::Human::getAngle()
{
	return m_Body->GetAngle();
}
