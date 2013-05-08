#pragma once

#include "..\..\stdafx.h"

namespace Mad
{
	namespace Interface
	{
		class IPhysicsSystem
			: public b2ContactListener
		{
		private:
			b2World* m_World;
			float m_FixedTimestepAccumulator;
			float m_FixedTimestepAccumulatorRatio;
			static const float FIXED_TIMESTEP;
			int m_VelIter;
			int m_PosIter;

		protected:			
			void smoothStates();
			void resetSmoothStates();

		public:
			IPhysicsSystem(b2World* World);
			~IPhysicsSystem();

			void update(float dt);
			void singleStep(float dt);
		};
	}
}