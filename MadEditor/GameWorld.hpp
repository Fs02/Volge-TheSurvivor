#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "iworldlistener.h"
#include <Interface/IGame.hpp>
#include <Entity/EntityManager.hpp>
#include <QWidget>

class GameWorld : public QObject
{
    Q_OBJECT

public:
    GameWorld();
    ~GameWorld();

    void update();

    void setListener(IWorldListener* listener);

    static void initialiseMadEngine(QWidget* renderViewport);
    static void deinitialiseMadEngine();

public slots:
    void onAddObject();

private:
    static QWidget* ms_RenderViewport;
    EntityManager m_Manager;
    IWorldListener* m_Listener;

    GameWorld(const GameWorld&);
};

#endif // GAMEWORLD_HPP
