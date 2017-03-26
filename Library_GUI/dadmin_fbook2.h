#ifndef DADMIN_FBOOK2_H
#define DADMIN_FBOOK2_H

#include <QDialog>

namespace Ui {
    class DAdmin_FBook2;
}

class DAdmin_FBook2 : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_FBook2(QWidget *parent = 0);
    ~DAdmin_FBook2();

private slots:
    void on_pushButton_Find_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::DAdmin_FBook2 *ui;
};

#endif // DADMIN_FBOOK2_H
