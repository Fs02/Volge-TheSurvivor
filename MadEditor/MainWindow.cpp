#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Editor(nullptr)
{
    ui->setupUi(this);

    m_UpdateTimer.setInterval(0);
    m_UpdateTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewWorld()
{
    delete m_Editor;
    m_Editor=new Editor();
    m_Editor->connect(m_UpdateTimer, SIGNAL(timeout()), SLOT(onUpdate()));
    m_Editor->connect(ui->actionAdd_entity, SIGNAL(triggered()), SLOT(onAddEntity()));
}

void MainWindow::onOpenWorld()
{

}
