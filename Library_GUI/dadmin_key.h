#ifndef DADMIN_KEY_H
#define DADMIN_KEY_H

#include <QDialog>

namespace Ui {
    class DAdmin_Key;
}

class DAdmin_Key : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_Key(QWidget *parent = 0);
    ~DAdmin_Key();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DAdmin_Key *ui;
};

#endif // DADMIN_KEY_H
