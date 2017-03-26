#include "dmain1.h"
#include "ui_dmain1.h"
#include "global_define.h"
#include "logbook.h"
#include "function.h"
#include <QString>
#include <string>

DMain1::DMain1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DMain1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);


    // set the day//
    string s11 = "Day "+ Convert_longtostr(Day);
    QString s = Convert_strtoqstr(s11);
    ui->label_Day->setText(s);
    // set the day//

    //set the time and thread
    setMouseTracking(true);
    Time_Start = QTime::currentTime();
    Thread.start();
}

void DMain1::Day_Add(){
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

DMain1::~DMain1()
{
    Thread.stop();

    delete ui;
}


void DMain1::mouseMoveEvent(QMouseEvent *){
    Time_Start = QTime::currentTime();
}
void DMain1::mousePressEvent(QMouseEvent *){
    Time_Start = QTime::currentTime();
}

void DMain1::keyPressEvent(QKeyEvent *){
    Time_Start = QTime::currentTime();
}

void DMain1::on_pushButton_Change_clicked()
{
    Thread.stop();
    uiset = 2;

    close();
}

void DMain1::on_pushButton_Login_clicked()
{
    Thread.stop();
    uiset = 4;

    close();
}

void DMain1::on_pushButton_Theme_clicked()
{
    Thread.stop();
    uiset = 3;

    close();
}

void DMain1::on_pushButton_Quit_clicked()
{
    Thread.stop();
    SysRun = false;

    close();
}
