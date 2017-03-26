#include "dmain2.h"
#include "ui_dmain2.h"
#include "global_define.h"
#include "function.h"
#include "logbook.h"
#include <QString>
#include <string>

DMain2::DMain2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DMain2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // set the day//
    string s11 = "Day "+ Convert_longtostr(Day);
    QString s = Convert_strtoqstr(s11);
    ui->label_Day->setText(s);
    // set the day//
}

DMain2::~DMain2()
{
    delete ui;
}

void DMain2::on_pushButton_clicked()
{
    uiset = 2;

    close();
}

void DMain2::on_pushButton_2_clicked()
{
    uiset = 4;

    close();
}

void DMain2::on_pushButton_Theme_clicked()
{
    uiset = 3;

    close();
}

void DMain2::on_pushButton_3_clicked()
{
    Day += 1;

    //log book
    FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));
    Logs L(Day, true);

    FlashDay();


    // set the day//
    string s11 = "Day "+ Convert_longtostr(Day);
    QString s = Convert_strtoqstr(s11);
    ui->label_Day->setText(s);
    // set the day//

}

void DMain2::on_pushButton_4_clicked()
{
    SysRun=false;

    close();
}
