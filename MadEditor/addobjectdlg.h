#ifndef ADDOBJECTDLG_H
#define ADDOBJECTDLG_H

#include <QDialog>

namespace Ui {
class AddObjectDlg;
}

class AddObjectDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddObjectDlg(QWidget *parent = 0);
    ~AddObjectDlg();

    QString entityName() const;
    
private:
    Ui::AddObjectDlg *ui;
};

#endif // ADDOBJECTDLG_H
