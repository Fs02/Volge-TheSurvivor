#pragma once

#include "../../stdafx.h"
#include "../../MadEngine/MadEngine.hpp"
#include "../ICEntity.hpp"

namespace CEntity
{
	namespace CSkeleton
	{
		class Human
			: public CEntity::ICEntity
		{
		private:
			void updateFriction();
			float m_Speed;
			int m_State;

		protected:
			Human(PhysicsSystem* physicsInstance, int catBits);
			~Human();

			b2Body* m_Body;
			void update(float deltaTime);
			void onCollisionBegin(Entity::IEntity* other);
			void onCollisionEnd(Entity::IEntity* other);

			void setSpeed(float speed);
			void setState(int state);

		public:
			const b2Vec2& getPosition();
			b2Vec2 getNormal();
			float getAngle();
		};
	}
}
