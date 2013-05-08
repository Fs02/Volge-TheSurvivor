#include "stdafx.h"
#include "IPhysicsSystem.hpp"

const float Mad::Interface::IPhysicsSystem::FIXED_TIMESTEP = 1/60.f;

Mad::Interface::IPhysicsSystem::IPhysicsSystem(b2World* World)
	: m_FixedTimestepAccumulator(0),
	  m_FixedTimestepAccumulatorRatio(0),
	  m_VelIter(1),
	  m_PosIter(1)
{
	m_World			= World;
}

Mad::Interface::IPhysicsSystem::~IPhysicsSystem()
{
	m_World			= nullptr;
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