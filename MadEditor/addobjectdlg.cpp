#include "addobjectdlg.h"
#include "ui_addobjectdlg.h"

AddObjectDlg::AddObjectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddObjectDlg)
{
    ui->setupUi(this);
}

AddObjectDlg::~AddObjectDlg()
{
    delete ui;
}

QString AddObjectDlg::entityName() const
{
    return ui->entityName->text();
}
