#ifndef DUSER_CONVERT_H
#define DUSER_CONVERT_H

#include <QDialog>

namespace Ui {
    class DUser_Convert;
}

class DUser_Convert : public QDialog
{
    Q_OBJECT

public:
    explicit DUser_Convert(QWidget *parent = 0);
    ~DUser_Convert();

private slots:
    void on_pushButton_Borrow_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::DUser_Convert *ui;
};

#endif // DUSER_CONVERT_H
