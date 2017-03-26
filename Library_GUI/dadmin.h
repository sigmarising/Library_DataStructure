#ifndef DADMIN_H
#define DADMIN_H

#include <QDialog>

namespace Ui {
    class DAdmin;
}

class DAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin(QWidget *parent = 0);
    ~DAdmin();

private slots:
    void on_pushButton_NewBook_clicked();

    void on_pushButton_NewPerson_clicked();

    void on_pushButton_FindBook_clicked();

    void on_pushButton_FindPerson_clicked();

    void on_pushButton_Logout_clicked();

private:
    Ui::DAdmin *ui;
};

#endif // DADMIN_H
