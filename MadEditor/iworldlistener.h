#ifndef IWORLDLISTENER_H
#define IWORLDLISTENER_H

#include <Entity/Entity.hpp>
#include <QString>

class IWorldListener
{
public:
    virtual ~IWorldListener(){}

    virtual void onEntityAdded(const QString& name, Entity* ent)=0;
};

#endif // IWORLDLISTENER_H
