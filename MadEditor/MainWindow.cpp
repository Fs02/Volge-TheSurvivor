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

void MainWindow::onCreateNewWorld()
{
    delete m_World;
    m_World=new GameWorld();
}

void MainWindow::onOpenWorld()
{
    delete m_World;
    m_World=new GameWorld();
}

void MainWindow::onUpdateWorld()
{
    if(m_World)
        m_World->update();
}
