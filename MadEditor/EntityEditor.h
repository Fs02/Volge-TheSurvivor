#ifndef ENTITYEDITOR_H
#define ENTITYEDITOR_H

#include <QWidget>

namespace Ui {
class EntityEditor;
}

class EntityEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntityEditor(QWidget *parent = 0);
    ~EntityEditor();
    
private:
    Ui::EntityEditor *ui;
};

#endif // ENTITYEDITOR_H
