#include "stdafx.h"
#include "IPhysicsSystem.hpp"

namespace
{
	class RayCastCallback
			: public b2RayCastCallback
	{
	private:
		b2Fixture* m_Fix;
		b2Vec2 m_Origin;
		b2Vec2 m_Pos, m_Norm;

	public:
		RayCastCallback(const b2Vec2& origin)
			: m_Fix(nullptr), m_Origin(origin)
		{
		}

		float32 ReportFixture(b2Fixture* fix, const b2Vec2& pt, const b2Vec2& norm, float32 fraction)
		{
			if(m_Fix == nullptr)
			{
				m_Fix=fix;
				m_Pos=pt;
				m_Norm=norm;
				return 1;
			}

			float prevDist=(m_Origin-m_Pos).LengthSquared();
			float newDist=(m_Origin-pt).LengthSquared();

			if(prevDist > newDist)
			{
				m_Fix=fix;
				m_Pos=pt;
				m_Norm=norm;
			}

			return 1;
		}

		bool hit() const
		{
			return (m_Fix != nullptr);
		}

		b2Fixture* hitFixture()
		{
			return m_Fix;
		}

		const b2Vec2& hitPosition() const
		{
			return m_Pos;
		}

		const b2Vec2& hitNormal() const
		{
			return m_Norm;
		}
	};
}

const float Mad::Interface::IPhysicsSystem::FIXED_TIMESTEP = 1/60.f;

Mad::Interface::IPhysicsSystem::IPhysicsSystem(b2World* World)
	: m_FixedTimestepAccumulator(0),
	  m_FixedTimestepAccumulatorRatio(0),
	  m_VelIter(1),
	  m_PosIter(1),
	  m_dbgDraw(nullptr)
{
	m_World			= World;
}

Mad::Interface::IPhysicsSystem::~IPhysicsSystem()
{
	delete m_World;
}

void Mad::Interface::IPhysicsSystem::enableDebugDraw(sf::RenderWindow& wnd)
{
	if(m_dbgDraw)
		return;

	m_dbgDraw=new DebugDraw(wnd);
	m_dbgDraw->SetFlags(~0);
	m_World->SetDebugDraw(m_dbgDraw);
}

void Mad::Interface::IPhysicsSystem::disableDebugDraw()
{
	m_World->SetDebugDraw(nullptr);
	delete m_dbgDraw;
	m_dbgDraw=nullptr;
}

void Mad::Interface::IPhysicsSystem::drawDebugData()
{
	if(!m_dbgDraw)
		return;

	m_World->DrawDebugData();
}

void Mad::Interface::IPhysicsSystem::smoothStates()
{
	/*
	const float dt = m_FixedTimestepAccumulatorRatio * FIXED_TIMESTEP;
 
	for (b2Body * b = m_World->GetBodyList (); b != NULL; b = b->GetNext ())
	{
		if (b->GetType () == b2_staticBody)
		{
			continue;
		}
 
		b2Vec2 smoothedPosition = b->GetPosition () + dt * b->GetLinearVelocity ();
		float smoothedAngle = b->GetAngle () + dt * b->GetAngularVelocity ();
		
		b->SetTransform(smoothedPosition, smoothedAngle);
	}
	*/
}

void Mad::Interface::IPhysicsSystem::resetSmoothStates()
{
	/*
	for (b2Body * b = m_World->GetBodyList (); b != NULL; b = b->GetNext ())
	{
		if (b->GetType () == b2_staticBody)
		{
			continue;
		}

		b2Vec2 smoothedPosition = b->GetPosition ();
		float smoothedAngle = b->GetAngle ();
		b->SetTransform(smoothedPosition, smoothedAngle);
	}
	*/
}

b2Fixture* Mad::Interface::IPhysicsSystem::internalClosestRayCastResult(
		const b2Vec2& start, const b2Vec2& end)
{
	RayCastCallback cb(start);
	m_World->RayCast(&cb, start, end);
	return cb.hitFixture();
}

void Mad::Interface::IPhysicsSystem::update(float dt)
{
	// Maximum number of steps, to avoid degrading to an halt.
	const int MAX_STEPS = 5;
 
	m_FixedTimestepAccumulator += dt;
	const int nSteps = static_cast<int> (
		std::floor (m_FixedTimestepAccumulator / FIXED_TIMESTEP)
	);
	// To avoid rounding errors, touches fixedTimestepAccumulator_ only
	// if needed.
	if (nSteps > 0)
	{
		m_FixedTimestepAccumulator -= nSteps * FIXED_TIMESTEP;
	}
 
	assert (
		"Accumulator must have a value lesser than the fixed time step" &&
		m_FixedTimestepAccumulator < FIXED_TIMESTEP + FLT_EPSILON
	);
	
	m_FixedTimestepAccumulatorRatio = m_FixedTimestepAccumulator / FIXED_TIMESTEP;
 
	// This is similar to clamp "dt":
	//	dt = std::min (dt, MAX_STEPS * FIXED_TIMESTEP)
	// but it allows above calculations of fixedTimestepAccumulator_ and
	// fixedTimestepAccumulatorRatio_ to remain unchanged.
	const int nStepsClamped = std::min (nSteps, MAX_STEPS);
	for (int i = 0; i < nStepsClamped; ++ i)
	{
		// In singleStep_() the CollisionManager could fire custom
		// callbacks that uses the smoothed states. So we must be sure
		// to reset them correctly before firing the callbacks.
		resetSmoothStates();
		singleStep (FIXED_TIMESTEP);
	}
 
	m_World->ClearForces ();
 
	// We "smooth" positions and orientations using
	// fixedTimestepAccumulatorRatio_ (alpha).
	smoothStates();
}

void Mad::Interface::IPhysicsSystem::singleStep(float dt)
{
	m_World->Step(dt, m_VelIter, m_PosIter);
}

b2Body* Mad::Interface::IPhysicsSystem::createBody(const b2BodyDef& bd)
{
	return m_World->CreateBody(&bd);
}

void Mad::Interface::IPhysicsSystem::destroyBody(b2Body* bd)
{
	m_World->DestroyBody(bd);
}
