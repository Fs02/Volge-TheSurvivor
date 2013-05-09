#pragma once

#include "../stdafx.h"
#include "../MadEngine/MadEngine.hpp"

namespace Entity
{
	class IEntity
	{
	protected:
		std::string m_Name;
		std::string m_FamilyName;

	public:
		IEntity();
		virtual ~IEntity();

		virtual void update(float deltaTime) = 0;
		virtual void onCollisionBegin(IEntity* other) = 0;
		virtual void onCollisionEnd(IEntity* other) = 0;
		virtual void draw() = 0;

		const std::string& getName() const;
		const std::string& getFamilyName() const;
	};
}
