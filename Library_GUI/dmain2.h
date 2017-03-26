#ifndef DMAIN2_H
#define DMAIN2_H

#include <QDialog>

namespace Ui {
    class DMain2;
}

class DMain2 : public QDialog
{
    Q_OBJECT

public:
    explicit DMain2(QWidget *parent = 0);
    ~DMain2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Theme_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DMain2 *ui;
};

#endif // DMAIN2_H
