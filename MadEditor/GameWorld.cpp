#include "GameWorld.hpp"
#include "addobjectdlg.h"
#include <QMessageBox>

QWidget* GameWorld::ms_RenderViewport=nullptr;

GameWorld::GameWorld()
    :m_Listener(nullptr)
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

void GameWorld::setListener(IWorldListener *listener)
{
    m_Listener=listener;
}

void GameWorld::initialiseMadEngine(QWidget *renderViewport)
{
    ms_RenderViewport=renderViewport;
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

void GameWorld::onAddObject()
{
    AddObjectDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.entityName().isEmpty())
            QMessageBox::warning(ms_RenderViewport, "MadEditor", "You haven't depcified the name of a new entity!", QMessageBox::Ok);
        else
        {
            Entity* ent=m_Manager.createEntity(dlg.entityName().toUtf8().data());
            if(!ent)
                QMessageBox::warning(ms_RenderViewport, "MadEditor", "Failed to add an entity with this name (does an entity with such name alredy exist?)", QMessageBox::Ok);
            else
                m_Listener->onEntityAdded(dlg.entityName(), ent);
        }
    }
}
