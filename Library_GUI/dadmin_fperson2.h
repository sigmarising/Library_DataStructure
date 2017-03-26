#ifndef DADMIN_FPERSON2_H
#define DADMIN_FPERSON2_H

#include <QDialog>

namespace Ui {
    class DAdmin_FPerson2;
}

class DAdmin_FPerson2 : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_FPerson2(QWidget *parent = 0);
    ~DAdmin_FPerson2();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_Find_clicked();

private:
    Ui::DAdmin_FPerson2 *ui;
};

#endif // DADMIN_FPERSON2_H
