#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <QWidget>
#include <Entity/EntityManager.hpp>

class Editor : public QObject, public IEntityMgrListener
{
    Q_OBJECT

public:
    Editor();
    ~Editor();

    void onEntityAdded(const std::string &, Entity *);
    void onEntityRemoved(const std::string &, Entity *);

    std::list<std::string> listEntities() const;
    Entity* getEntity(const std::string& name);
    void selectEntityByName(const std::string& name);
    Entity* getSelectedEntity();

    static void initialiseEngine(QWidget* renderViewport);
    static void deinitialiseEngine();

public slots:
    void onUpdate();
    void onAddEntity();
    void onRemoveEntity(const std::string& name);
    void onAddComponent();
    void onRemoveComponent(Entity* ent, IComponent* comp);

signals:
    void updateEntityTree();
    void entitySelected();

private:
    EntityManager m_Manager;
    Entity* m_Selected;
};

#endif // EDITOR_HPP
