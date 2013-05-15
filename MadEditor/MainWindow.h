#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Editor.hpp"
#include <QMainWindow>
#include <QTimer>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setSelectedEntity(Entity* ent);

private slots:
    void onNewWorld();
    void onOpenWorld();

    void onEntitySelectedFromTree(QTreeWidgetItem* item, int);
    void onRemoveEntity();

    void onUpdateWorldTree();
    void onUpdateSelectedEnt();

signals:
    void selectedEntity(Entity* ent);
    
private:
    Ui::MainWindow *ui;
    QTimer m_UpdateTimer;
    Editor* m_Editor;
};

#endif // MAINWINDOW_H
