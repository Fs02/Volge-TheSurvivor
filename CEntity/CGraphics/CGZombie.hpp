#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../ICEntity.hpp"

namespace CEntity
{
	namespace CGraphics
	{
		class CGZombie
			: public CEntity::ICEntity
		{
		protected:
			CGZombie(PhysicsSystem* physicsInstance);
			~CGZombie();

			void update(float deltaTime);
			void setParams(const b2Vec2& pos, float angle, int state);

			Mad::Graphics::AniSprite m_AniSprite;

			int m_State;
			b2Vec2 m_Pos;
			float m_Angle;

		public:
			void draw();
		};
	}
}