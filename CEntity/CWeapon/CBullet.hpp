#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../ICEntity.hpp"

namespace CEntity
{
	class CBullet
	{
	private:
		b2Body* m_Body;
	public:
		CBullet(b2World* world, const b2Vec2& normal, const b2Vec2& pos, float rot);
		~CBullet();
	};
}
