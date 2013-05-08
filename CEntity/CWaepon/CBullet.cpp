#include "stdafx.h"
#include "CBullet.hpp"

CEntity::CBullet::CBullet(b2World* world, const b2Vec2& normal, const b2Vec2& pos, float rot)
{
	b2BodyDef bodyDef;
    bodyDef.type		= b2_dynamicBody;
    bodyDef.bullet		= true;
    bodyDef.position	= pos;
	bodyDef.angle		= rot;
    m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape	shape;
	shape.SetAsBox(0.01f, 0.05f);
    b2FixtureDef fixDef;
    fixDef.density = 0.1f;
    fixDef.shape = &shape;
	fixDef.filter.categoryBits = CEntity::BULLET;
    m_Body->CreateFixture(&fixDef);

    m_Body->ApplyLinearImpulse(normal, m_Body->GetWorldCenter());
	m_Body->SetUserData(this);
    
}

CEntity::CBullet::~CBullet()
{
	m_Body->GetWorld()->DestroyBody(m_Body);
}