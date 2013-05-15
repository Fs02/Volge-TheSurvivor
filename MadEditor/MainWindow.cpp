#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Editor(nullptr)
{
    ui->setupUi(this);

    Editor::initialiseEngine(ui->renderViewport);

    m_UpdateTimer.setInterval(500);
    m_UpdateTimer.start();

    this->connect(ui->actionNew, SIGNAL(triggered()), SLOT(onNewWorld()));
    this->connect(ui->actionOpen, SIGNAL(triggered()), SLOT(onOpenWorld()));
    this->connect(ui->actionRemove_entity, SIGNAL(triggered()), SLOT(onRemoveEntity()));
    this->connect(ui->worldTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(onEntitySelectedFromTree(QTreeWidgetItem*,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    Editor::deinitialiseEngine();
}

void MainWindow::onNewWorld()
{
    delete m_Editor;
    m_Editor=new Editor();
    m_Editor->connect(&m_UpdateTimer, SIGNAL(timeout()), SLOT(onUpdate()));
    this->connect(m_Editor, SIGNAL(updateEntityTree()), SLOT(onUpdateWorldTree()));
    this->connect(m_Editor, SIGNAL(entitySelected()), SLOT(onUpdateSelectedEnt()));
    m_Editor->connect(ui->actionAdd_entity, SIGNAL(triggered()), SLOT(onAddEntity()));
}

void MainWindow::onOpenWorld()
{
    delete m_Editor;
    m_Editor=new Editor();
    m_Editor->connect(&m_UpdateTimer, SIGNAL(timeout()), SLOT(onUpdate()));
    this->connect(m_Editor, SIGNAL(updateEntityTree()), SLOT(onUpdateWorldTree()));
    this->connect(m_Editor, SIGNAL(entitySelected()), SLOT(onUpdateSelectedEnt()));
    m_Editor->connect(ui->actionAdd_entity, SIGNAL(triggered()), SLOT(onAddEntity()));
}

void MainWindow::onEntitySelectedFromTree(QTreeWidgetItem *item, int)
{
    if(!m_Editor || !item->parent())
        return;

    QString name=item->text(0);
    m_Editor->selectEntityByName(name.toUtf8().data());
}

void MainWindow::onRemoveEntity()
{
    if(!m_Editor)
        return;

    QTreeWidgetItem* item=ui->worldTree->currentItem();
    if(!item || !item->parent())
        return;

    QString name=item->text(0);
    m_Editor->getEntity(name.toUtf8().data())->markAsRedundant();
}

void MainWindow::onUpdateWorldTree()
{
    ui->worldTree->clear();

    QTreeWidgetItem* sector=new QTreeWidgetItem();
    sector->setText(0, "Sector 0");
    std::list<std::string> ents=m_Editor->listEntities();
    for(auto iter=ents.begin(); iter != ents.end(); ++iter)
    {
        QTreeWidgetItem* item=new QTreeWidgetItem(sector);
        item->setText(0, iter->c_str());
    }
    ui->worldTree->addTopLevelItem(sector);
}

void MainWindow::onUpdateSelectedEnt()
{
    Entity* sel=m_Editor->getSelectedEntity();

    ui->compList->clear();
    ui->compPropsTable->clear();

    if(!sel)
        return;

    std::list<IComponent*> comps=sel->listComponents();
    for(auto iter=comps.begin(); iter != comps.end(); ++iter)
    {
        QListWidgetItem* item=new QListWidgetItem();
        item->setText((*iter)->getTypeName().c_str());
        ui->compList->addItem(item);
    }
}
