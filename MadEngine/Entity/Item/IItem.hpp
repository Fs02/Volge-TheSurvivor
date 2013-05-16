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
        virtual std::string getName() const=0;
        virtual bool compare(const IItem* other) const=0; // used by InventoryComponent to put items on stacks
	};
}
