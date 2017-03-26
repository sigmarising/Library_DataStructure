#ifndef DUSER_BORROW_H
#define DUSER_BORROW_H

#include <QDialog>

namespace Ui {
    class DUser_Borrow;
}

class DUser_Borrow : public QDialog
{
    Q_OBJECT

public:
    explicit DUser_Borrow(QWidget *parent = 0);
    ~DUser_Borrow();

private slots:
    void on_pushButton_Find_clicked();

    void on_pushButton_Borow_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::DUser_Borrow *ui;
};

#endif // DUSER_BORROW_H
