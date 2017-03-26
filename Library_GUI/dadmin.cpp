#include "dadmin.h"
#include "ui_dadmin.h"
#include "global_define.h"
#include "logbook.h"

DAdmin::DAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DAdmin::~DAdmin()
{
    delete ui;
}

void DAdmin::on_pushButton_NewBook_clicked()
{
    uiset = 6;

    close();
}

void DAdmin::on_pushButton_NewPerson_clicked()
{
    uiset = 8;

    close();
}

void DAdmin::on_pushButton_FindBook_clicked()
{
    uiset = 9;

    close();
}

void DAdmin::on_pushButton_FindPerson_clicked()
{
    uiset = 10;

    close();
}

void DAdmin::on_pushButton_Logout_clicked()
{
    uiset = 1;

    Logs L(Day, false);
    L.Log_Logout("Admin");

    close();
}
