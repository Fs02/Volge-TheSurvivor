#ifndef INVENTORYCOMPONENT_HPP
#define INVENTORYCOMPONENT_HPP

#include "../Entity.hpp"
#include "../Item/IItem.hpp"
#include "TransformableComponent.hpp"
#include <deque>

class InventoryComponent : public IComponent
{
public:
    InventoryComponent();
    ~InventoryComponent();

    std::string getTypeName() const;
    std::list<Property> listProperties() const;

    Item::IItem* getItem(int index);
    Item::IItem* getItem(const std::string& name);

    int getItemTypesCount() const;
    void addItem(Item::IItem* item);
    void removeItem(Item::IItem* item);
    bool dropItem(int typeIndex);
    void dropAllItems();

    void initialise(Entity *owner);
    void update(float);
    void onCollisionBegin(Entity *);
    void onCollisionEnd(Entity *);

	static IComponent* factoryFunction(rapidxml::xml_node<>* comp_data);

private:
    typedef std::deque<Item::IItem*> ItemStack;
    TransformableComponent* m_Transform;
    std::vector<ItemStack> m_Items;
};

#endif // INVENTORYCOMPONENT_HPP
