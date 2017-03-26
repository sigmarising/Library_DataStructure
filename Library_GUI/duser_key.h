#ifndef DUSER_KEY_H
#define DUSER_KEY_H

#include <QDialog>

namespace Ui {
    class DUser_Key;
}

class DUser_Key : public QDialog
{
    Q_OBJECT

public:
    explicit DUser_Key(QWidget *parent = 0);
    ~DUser_Key();

private slots:
    void on_pushButton_Change_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::DUser_Key *ui;
};

#endif // DUSER_KEY_H
