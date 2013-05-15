#include "Editor.hpp"
#include <Manager/Graphics.hpp>
#include <Manager/Controller.hpp>
#include <Manager/Resource.hpp>

Editor::Editor()
{
    m_Manager.setListener(this);
}

Editor::~Editor()
{
}

void Editor::onEntityAdded(const std::string &, Entity *)
{
    emit updateEntityTree();
}

void Editor::onEntityRemoved(const std::string &, Entity *)
{
    emit updateEntityTree();
}

std::list<std::string> Editor::listEntities() const
{
    return m_Manager.listEntities();
}

Entity* Editor::getEntity(const std::string &name)
{
    return m_Manager.getEntity(name);
}

void Editor::initialiseEngine(QWidget *renderViewport)
{
    Mad::Manager::Graphics::initialise();
    Mad::Manager::Graphics::getSingleton()->initialiseWithWindow(renderViewport->winId());
    Mad::Manager::Controller::initialise();
    Mad::Manager::Resource::initialise();
}

void Editor::deinitialiseEngine()
{
    Mad::Manager::Graphics::deinitialise();
    Mad::Manager::Controller::deinitialise();
    Mad::Manager::Resource::deinitialise();
}

void Editor::onUpdate()
{
    Mad::Manager::Graphics* graph=Mad::Manager::Graphics::getSingleton();

    graph->beginGameRendering();
    graph->getRenderTarget().clear();
    m_Manager.update(0);
    graph->endGameRendering();
}

void Editor::onAddEntity()
{
    // TODO: add entity dialog
    m_Manager.createEntity("Enitity");
}

void Editor::onRemoveEntity(const std::string &name)
{
    m_Manager.getEntity(name)->markAsRedundant();
}

void Editor::onAddComponent()
{
    // TODO add component dialog
}

void Editor::onRemoveComponent(Entity *ent, IComponent *comp)
{
    ent->removeComponent(comp);
    ent->initialise();
}
