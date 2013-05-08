//
//Human Skeleton will automatically have a censor.
//the Category Bits of the censor equivalent to m_Body category Bits + 1
//

#pragma once

#include "..\..\stdafx.h"
#include "..\ICSkeleton.hpp"
#include "..\..\MadEngine\MadEngine.hpp"

namespace CEntity
{
	namespace CSkeleton
	{
		class Human
			:public CEntity::ICSkeleton
		{
		private:
			void updateFriction();
			float m_Speed;

		protected:
			Human(b2World* world, int catBits);
			~Human();
			void updateSkeleton(int state);
			void setSpeed(float speed);
		};
	}
}