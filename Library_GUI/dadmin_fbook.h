#ifndef DADMIN_FBOOK_H
#define DADMIN_FBOOK_H

#include <QDialog>

namespace Ui {
    class DAdmin_FBook;
}

class DAdmin_FBook : public QDialog
{
    Q_OBJECT

public:
    explicit DAdmin_FBook(QWidget *parent = 0);
    ~DAdmin_FBook();

private slots:
    void on_pushButton_Find_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_clicked();

private:
    Ui::DAdmin_FBook *ui;
};

#endif // DADMIN_FBOOK_H
