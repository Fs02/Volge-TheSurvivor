#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameWorld.hpp"
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onCreateNewWorld();
    void onOpenWorld();

    void onUpdateWorld();
    
private:
    Ui::MainWindow *ui;
    GameWorld* m_World;
    QTimer m_UpdateTimer;
};

#endif // MAINWINDOW_H
