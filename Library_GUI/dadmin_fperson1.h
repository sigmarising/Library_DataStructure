#ifndef DADMIN_FPERSON1_H
#define DADMIN_FPERSON1_H

#include <QDialog>

namespace Ui {
    class DAdmin_FPerson1;
}

class DAdmin_FPerson1 : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_FPerson1(QWidget *parent = 0);
    ~DAdmin_FPerson1();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::DAdmin_FPerson1 *ui;
};

#endif // DADMIN_FPERSON1_H
