#ifndef PICKUPABLECOMPONENT_HPP
#define PICKUPABLECOMPONENT_HPP

#include "../Entity.hpp"
#include "../Item/IItem.hpp"
#include "SpriteComponent.hpp"

class PickUpAbleComponent : public IComponent
{
public:
    PickUpAbleComponent();
    ~PickUpAbleComponent();

    std::string getTypeName() const;
    std::list<Property> listProperties() const;

    void changeItem(Item::IItem* item);
    const Item::IItem* getItem() const;
    Item::IItem* orphanItem(); // passes ownership over m_Item to the caller

    void initialise(Entity *owner);
    void update(float);

private:
    Item::IItem* m_Item;
    bool m_ItemChanged;
    SpriteComponent* m_Sprite;
};

#endif // PICKUPABLECOMPONENT_HPP
