#ifndef DMAINC_H
#define DMAINC_H

#include <QDialog>

namespace Ui {
    class DMainC;
}

class DMainC : public QDialog
{
    Q_OBJECT

public:
    explicit DMainC(QWidget *parent = 0);
    ~DMainC();

private slots:
    void on_pushButton_Auto_clicked();

    void on_pushButton_Manual_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::DMainC *ui;
};

#endif // DMAINC_H
