#pragma once

#include <string>

/*
 * Items that player can pick-up
 */
namespace Item
{
	namespace ItemClass
	{
		enum Enum{ PickUp, Weapon };
	}

	class IItem
	{
	public:
		virtual ~IItem(){}

		virtual ItemClass::Enum getClass() const=0;
	};
}
