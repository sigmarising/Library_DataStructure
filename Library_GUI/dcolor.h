#ifndef DCOLOR_H
#define DCOLOR_H

#include <QDialog>

namespace Ui {
    class DColor;
}

class DColor : public QDialog
{
    Q_OBJECT

public:
    explicit DColor(QWidget *parent = 0);
    ~DColor();

private slots:
    void on_Color_Blue_clicked();

    void on_Color_Green_clicked();

    void on_Color_Pink_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::DColor *ui;
};

#endif // DCOLOR_H
