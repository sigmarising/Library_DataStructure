#ifndef DUSER_RETURN_H
#define DUSER_RETURN_H

#include <QDialog>

namespace Ui {
    class DUser_Return;
}

class DUser_Return : public QDialog
{
    Q_OBJECT

public:
    explicit DUser_Return(QWidget *parent = 0);
    ~DUser_Return();

private slots:
    void on_pushButton_BookReturn_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::DUser_Return *ui;
};

#endif // DUSER_RETURN_H
