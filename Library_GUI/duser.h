#ifndef DUSER_H
#define DUSER_H

#include <QDialog>

namespace Ui {
    class DUser;
}

class DUser : public QDialog
{
    Q_OBJECT

public:
    explicit DUser(QWidget *parent = 0);
    ~DUser();

private slots:
    void on_pushButton_Borrow_clicked();

    void on_pushButton_Return_clicked();

    void on_pushButton_Convert_clicked();

    void on_pushButton_PayMoney_clicked();

    void on_pushButton_ChangeKey_clicked();

    void on_pushButton_Logout_clicked();

private:
    Ui::DUser *ui;
};

#endif // DUSER_H
