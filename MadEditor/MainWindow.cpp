#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_World(nullptr)
{
    ui->setupUi(this);

    GameWorld::initialiseMadEngine(ui->renderViewport);

    m_UpdateTimer.setInterval(0);
    m_UpdateTimer.start();
    this->connect(&m_UpdateTimer, SIGNAL(timeout()), SLOT(onUpdateWorld()));

    this->connect(ui->actionNew, SIGNAL(triggered()), SLOT(onCreateNewWorld()));
    this->connect(ui->actionOpen, SIGNAL(triggered()), SLOT(onOpenWorld()));
}

MainWindow::~MainWindow()
{
    delete m_World;
    GameWorld::deinitialiseMadEngine();
    delete ui;
}

void MainWindow::onEntityAdded(const QString &name, Entity *ent)
{
    QTreeWidgetItem* item=new QTreeWidgetItem();
    item->setText(0, name);
    QVariant var;
    var.setValue<void*>(ent);
    item->setData(0, Qt::UserRole, var);
    ui->worldTree->addTopLevelItem(item);
}

void MainWindow::onCreateNewWorld()
{
    delete m_World;
    m_World=new GameWorld();
    m_World->setListener(this);
    QObject::connect(ui->actionAdd_entity, SIGNAL(triggered()), m_World, SLOT(onAddObject()));
}

void MainWindow::onOpenWorld()
{
    delete m_World;
    m_World=new GameWorld();
    m_World->setListener(this);
    QObject::connect(ui->actionAdd_entity, SIGNAL(triggered()), m_World, SLOT(onAddObject()));
}

void MainWindow::onUpdateWorld()
{
    if(m_World)
        m_World->update();
}

void MainWindow::onEntitySelected(QTreeWidgetItem *item)
{
    QVariant userData=item->data(0, Qt::UserRole);
    Entity* ent=(Entity*)userData.value<void*>();
    if(ent)
        this->m_initEntityEditor(ent);
}

void MainWindow::m_initEntityEditor(Entity *ent)
{
    ui->objectTree->clear();

    std::list<const IComponent*> comps=ent->listComponents();
    for(auto iter=comps.begin(); iter != comps.end(); ++iter)
    {
        std::list<Property> props=(*iter)->listProperties();
        QTreeWidgetItem* compItem=new QTreeWidgetItem();
        compItem->setText(0, (*iter)->getTypeName().c_str());
        for(auto i=props.begin(); i != props.end(); ++i)
        {
            QTreeWidgetItem* propItem=new QTreeWidgetItem(compItem);
            propItem->setText(0, i->getName().c_str());
        }
    }
}
