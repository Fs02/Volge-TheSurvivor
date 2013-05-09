//
// Skeleton is used by Entity object using Inheritance pattern
//
#pragma once

#include "../stdafx.h"
#include "../MadEngine/MadEngine.hpp"
#include "EnumStates.hpp"

namespace CEntity
{
	//Category Bits
	enum {
		UNDEFINED	= 0x0001, 
		CIVILIAN	= 0x0002,
		SOLDIER		= 0x0004,
		ZOMBIE		= 0x0008,
		CENSOR		= 0x0016,	  
		BULLET		= 0x0032
	};

	struct PhysicsComponent  {
	float32 previousAngle;
	float32 smoothedAngle;
	b2Vec2 previousPosition;
	b2Vec2 smoothedPosition;
	};

	class ICSkeleton
	{
	protected:


		b2Body* m_Body;
		Mad::Manager::Controller* m_Controller;

		virtual void updateSkeleton(int state) = 0;

	public:		
		ICSkeleton();
		virtual ~ICSkeleton();
		const b2Vec2& getPosition();
		b2Vec2 getNormal();
		float getAngle();
	};
}
