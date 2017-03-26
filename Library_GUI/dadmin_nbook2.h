#ifndef DADMIN_NBOOK2_H
#define DADMIN_NBOOK2_H

#include <QDialog>

namespace Ui {
    class DAdmin_NBook2;
}

class DAdmin_NBook2 : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_NBook2(QWidget *parent = 0);
    ~DAdmin_NBook2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DAdmin_NBook2 *ui;
};

#endif // DADMIN_NBOOK2_H
