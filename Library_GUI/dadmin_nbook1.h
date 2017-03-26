#ifndef DADMIN_NBOOK1_H
#define DADMIN_NBOOK1_H

#include <QDialog>

namespace Ui {
    class DAdmin_NBook1;
}

class DAdmin_NBook1 : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_NBook1(QWidget *parent = 0);
    ~DAdmin_NBook1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DAdmin_NBook1 *ui;
};

#endif // DADMIN_NBOOK1_H
