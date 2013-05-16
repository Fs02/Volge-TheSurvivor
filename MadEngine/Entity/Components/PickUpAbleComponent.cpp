#include "PickUpAbleComponent.hpp"

PickUpAbleComponent::PickUpAbleComponent()
    :m_Item(nullptr), m_ItemChanged(false)
{
}

PickUpAbleComponent::~PickUpAbleComponent()
{
    delete m_Item;
}

std::string PickUpAbleComponent::getTypeName() const
{
    return "PickUp-able";
}

std::list<Property> PickUpAbleComponent::listProperties() const
{
    return std::list<Property>();
}

void PickUpAbleComponent::changeItem(Item::IItem *item)
{
    delete m_Item;
    m_Item=item;
    m_ItemChanged=true;
}

const Item::IItem* PickUpAbleComponent::getItem() const
{
    return m_Item;
}

Item::IItem* PickUpAbleComponent::orphanItem()
{
    Item::IItem* item=m_Item;
    m_Item=nullptr;
    m_ItemChanged=true;
    return item;
}

void PickUpAbleComponent::initialise(Entity *owner)
{
    m_Sprite=owner->component<SpriteComponent>();
    m_ItemChanged=true;
}

void PickUpAbleComponent::update(float)
{
    if(m_ItemChanged && m_Sprite)
    {
        if(!m_Item)
            m_Sprite->setSprite(std::string());
        else
            m_Sprite->setSprite(m_Item->getIconName());

        m_ItemChanged=false;
    }
}
