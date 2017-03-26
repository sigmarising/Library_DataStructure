#ifndef DADMIN_NPERSON_H
#define DADMIN_NPERSON_H

#include <QDialog>

namespace Ui {
    class DAdmin_NPerson;
}

class DAdmin_NPerson : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_NPerson(QWidget *parent = 0);
    ~DAdmin_NPerson();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DAdmin_NPerson *ui;
};

#endif // DADMIN_NPERSON_H
