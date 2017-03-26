#include "dmainc.h"
#include "ui_dmainc.h"
#include "global_define.h"
#include <QMessageBox>

DMainC::DMainC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DMainC)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DMainC::~DMainC()
{
    delete ui;
}

void DMainC::on_pushButton_Auto_clicked()
{
    Manual_Time = false;

    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("切换至自动计时"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //
}

void DMainC::on_pushButton_Manual_clicked()
{
    Manual_Time = true;

    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("切换至手动计时"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //
}

void DMainC::on_pushButton_Back_clicked()
{
    uiset = 1;

    close();
}
