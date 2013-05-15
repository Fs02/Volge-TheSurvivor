#include "EntityEditor.h"
#include "ui_entityeditor.h"

EntityEditor::EntityEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityEditor)
{
    ui->setupUi(this);
}

EntityEditor::~EntityEditor()
{
    delete ui;
}
