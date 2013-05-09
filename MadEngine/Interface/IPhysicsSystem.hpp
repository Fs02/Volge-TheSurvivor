#pragma once

#include "../../stdafx.h"
#include "../3rdParty/b2DebugDraw/DebugDraw.hpp"

namespace Mad
{
	namespace Interface
	{
		class IPhysicsSystem
		{
		protected:
			b2World* m_World;
			float m_FixedTimestepAccumulator;
			float m_FixedTimestepAccumulatorRatio;
			static const float FIXED_TIMESTEP;
			int m_VelIter;
			int m_PosIter;

			DebugDraw* m_dbgDraw;

			void smoothStates();
			void resetSmoothStates();
			// helper function used by PhysicsSystem
			b2Fixture* internalClosestRayCastResult(const b2Vec2& start, const b2Vec2& end);

		public:
			IPhysicsSystem(b2World* World);
			virtual ~IPhysicsSystem();

			void enableDebugDraw(sf::RenderWindow& wnd);
			void disableDebugDraw();
			void drawDebugData();

			void update(float dt);
			void singleStep(float dt);

			b2Body* createBody(const b2BodyDef& bd);
		};
	}
}
