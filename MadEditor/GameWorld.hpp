#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <Interface/IGame.hpp>
#include <Entity/EntityManager.hpp>
#include <QWidget>

class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    void update();

    static void initialiseMadEngine(QWidget* renderViewport);
    static void deinitialiseMadEngine();

private:
    EntityManager m_Manager;

    GameWorld(const GameWorld&);
};

#endif // GAMEWORLD_HPP
