#include "dcolor.h"
#include "ui_dcolor.h"
#include "global_define.h"
#include "function.h"
#include <QMessageBox>

DColor::DColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DColor)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DColor::~DColor()
{
    delete ui;
}

void DColor::on_Color_Blue_clicked()
{
    FileLine_Change("logbook\\sys.txt", 7, "1");
    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("重启应用后生效"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //
}

void DColor::on_Color_Green_clicked()
{
    FileLine_Change("logbook\\sys.txt", 7, "2");
    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("重启应用后生效"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //
}

void DColor::on_Color_Pink_clicked()
{
    FileLine_Change("logbook\\sys.txt", 7, "3");
    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("重启应用后生效"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //
}

void DColor::on_pushButton_Return_clicked()
{
    uiset = 1;

    close();
}
