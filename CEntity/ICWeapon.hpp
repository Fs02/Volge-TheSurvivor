#pragma once

#include "../stdafx.h"
#include "../MadEngine/MadEngine.hpp"

namespace CEntity
{
	namespace CWeapon
	{
		enum
		{
			MALE,
			GUN
		};
		class ICWaepon
		{
		private:
			int m_Type;
		public:
			ICWaepon(int type)
			{
				m_Type	= type;
			}

			~ICWaepon()
			{}
			int getType()
			{
				return m_Type;
			}
		};
	}
}
