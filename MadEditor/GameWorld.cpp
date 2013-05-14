#include "GameWorld.hpp"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::update()
{
    Mad::Manager::Graphics* graph=Mad::Manager::Graphics::getSingleton();
    graph->getRenderTarget().clear();

    graph->beginGameRendering();
    graph->endGameRendering();

    graph->beginRendering();
    graph->endRendering();

    graph->getRenderWindow().display();
}

void GameWorld::initialiseMadEngine(QWidget *renderViewport)
{
    Mad::Manager::GameState::initialise();
    Mad::Manager::Resource::initialise();
    Mad::Manager::Graphics::initialise();
    Mad::Manager::Graphics::getSingleton()->initialiseWithWindow(renderViewport->winId());
    Mad::Manager::Controller::initialise();
}

void GameWorld::deinitialiseMadEngine()
{
    Mad::Manager::GameState::deinitialise();
    Mad::Manager::Resource::deinitialise();
    Mad::Manager::Graphics::deinitialise();
    Mad::Manager::Controller::deinitialise();
}
