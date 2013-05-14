#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameWorld.hpp"
#include "iworldlistener.h"
#include <QMainWindow>
#include <QTimer>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IWorldListener
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void onEntityAdded(const QString &name, Entity *ent);

public slots:
    void onCreateNewWorld();
    void onOpenWorld();

    void onUpdateWorld();

    void onEntitySelected(QTreeWidgetItem* item);
    
private:
    Ui::MainWindow *ui;
    GameWorld* m_World;
    QTimer m_UpdateTimer;

    void m_initEntityEditor(Entity* ent);
};

#endif // MAINWINDOW_H
