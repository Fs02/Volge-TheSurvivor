#pragma once

#include "../../stdafx.h"
#include "../ICSkeleton.hpp"
#include "../../MadEngine/MadEngine.hpp"

namespace CEntity
{
	class CBullet
	{
	private:
		b2Body* m_Body;
	public:
		CBullet(b2World* world, const b2Vec2& normal, const b2Vec2& pos, float rot);
		~CBullet();

		void aaa()
		{
			std::cout<<"asdasdas";
		}
	};
}
