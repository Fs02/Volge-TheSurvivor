#include "InventoryComponent.hpp"
#include "PickUpAbleComponent.hpp"

InventoryComponent::InventoryComponent()
    :m_Transform(nullptr), m_PickUpAble(nullptr)
{
}

InventoryComponent::~InventoryComponent()
{
    this->dropAllItems();
}

std::string InventoryComponent::getTypeName() const
{
    return "Inventory";
}

std::list<Property> InventoryComponent::listProperties() const
{
    return std::list<Property>();
}

Item::IItem* InventoryComponent::getItem(int index)
{
    if(index < 0)
        return nullptr;

    int count=0;
    for(unsigned int tp=0; tp < m_Items.size(); ++tp)
    {
        for(unsigned int i=0; i < m_Items[tp].size(); ++i, ++count)
            if(count == index)
                return m_Items[tp][i];
    }

    return nullptr;
}

Item::IItem* InventoryComponent::getItem(const std::string &name)
{
    for(unsigned int tp=0; tp < m_Items.size(); ++tp)
        for(unsigned int i=0; i < m_Items[tp].size(); ++i)
            if(m_Items[tp][i]->getName() == name)
                return m_Items[tp][i];
    return nullptr;
}

int InventoryComponent::getItemTypesCount() const
{
    return m_Items.size();
}

void InventoryComponent::addItem(Item::IItem *item)
{
    for(unsigned int i=0; i < m_Items.size(); ++i)
    {
        if(item->compare(m_Items[i].front()) == 0)
        {
            m_Items[i].push_back(item);
            return;
        }
    }

    m_Items.push_back({item});
}

void InventoryComponent::removeItem(Item::IItem *item)
{
    for(unsigned int tp=0; tp < m_Items.size(); ++tp)
    {
        for(unsigned int i=0; i < m_Items[tp].size(); ++i)
        {
            if(m_Items[tp][i] == item)
            {
                m_Items[tp].erase(m_Items[tp].begin()+i);
                if(m_Items[tp].empty())
                    m_Items.erase(m_Items.begin()+tp);
                delete item;
                return;
            }
        }
    }
}

bool InventoryComponent::dropItem(int typeIndex)
{
    if(typeIndex >= (int)m_Items.size() || typeIndex < 0)
        return false;

    Item::IItem* it=m_Items[typeIndex].front();
    m_Items[typeIndex].pop_front();
    if(m_Items[typeIndex].empty())
        m_Items.erase(m_Items.begin()+typeIndex);

    // TODO creating an entity with PickUpAbleComponent
    // for now just delete an item so that we don't have a memory leak
    delete it;

    return true;
}

void InventoryComponent::dropAllItems()
{
    while(!m_Items.empty())
    {
        while(this->dropItem(0))
            continue;
    }
}

void InventoryComponent::pickUp()
{
    if(m_PickUpAble)
    {
        PickUpAbleComponent* comp=m_PickUpAble->component<PickUpAbleComponent>();
        Item::IItem* item=comp->orphanItem();
        if(item)
            this->addItem(item);
        m_PickUpAble->markAsRedundant();
        m_PickUpAble=nullptr;
    }
}

void InventoryComponent::initialise(Entity *owner)
{
    m_Transform=owner->component<TransformableComponent>();
}

void InventoryComponent::update(float)
{
}

void InventoryComponent::onCollisionBegin(Entity *ent)
{
    if(ent->component<PickUpAbleComponent>())
        m_PickUpAble=ent;
}

void InventoryComponent::onCollisionEnd(Entity *ent)
{
    if(m_PickUpAble == ent)
        m_PickUpAble=nullptr;
}
