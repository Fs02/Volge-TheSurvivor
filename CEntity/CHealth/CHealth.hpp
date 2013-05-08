#pragma once

#include "..\..\stdafx.h"

namespace CEntity
{
	class CHealth
	{
	private:
		int m_Health;
		const int m_MaxHealth;

	protected:
		CHealth(int Health);
		~CHealth();

	public:
		void increaseHealthPoints(int points = 1);
		void decreaseHealthPoints(int points = 1);

		int getHealthPoints();
	};
}