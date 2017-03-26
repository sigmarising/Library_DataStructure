#ifndef DMAIN1_H
#define DMAIN1_H

#include <QDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include "mythread.h"

namespace Ui {
    class DMain1;
}

class DMain1 : public QDialog
{
    Q_OBJECT

public:
    explicit DMain1(QWidget *parent = 0);

    void Day_Add();

    ~DMain1();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_pushButton_Change_clicked();

    void on_pushButton_Login_clicked();

    void on_pushButton_Theme_clicked();

    void on_pushButton_Quit_clicked();

private:
    Ui::DMain1 *ui;

    MyThread Thread;
};

#endif // DMAIN1_H
