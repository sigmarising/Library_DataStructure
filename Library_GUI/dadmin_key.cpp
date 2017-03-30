#include "dadmin_key.h"
#include "ui_dadmin_key.h"
#include "function.h"
#include "global_define.h"
#include <QMessageBox>
#include <string>

DAdmin_Key::DAdmin_Key(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_Key)
{
    ui->setupUi(this);
}

DAdmin_Key::~DAdmin_Key()
{
    delete ui;
}

void DAdmin_Key::on_pushButton_2_clicked()
{
    uiset = 5;

    close();
}

void DAdmin_Key::on_pushButton_clicked()
{
    string keyold = Convert_qstrtostr(ui->lineEdit_Old->text());

    if (keyold == FileLine_Getline("logbook\\sys.txt",2)){
        string key1 = Convert_qstrtostr(ui->lineEdit_New1->text());
        string key2 = Convert_qstrtostr(ui->lineEdit_New2->text());

        if(key1 == key2){
            FileLine_Change("logbook\\sys.txt",2,key1);
            // MessageBox //
            QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("修改成功"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //
            ui->lineEdit_Old->clear();
            ui->lineEdit_New1->clear();
            ui->lineEdit_New2->clear();

        }
        else{
            // MessageBox //
            QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("新密码不一致"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //
            ui->lineEdit_Old->clear();
            ui->lineEdit_New1->clear();
            ui->lineEdit_New2->clear();
            ui->lineEdit_Old->setFocus();
        }
    }
    else{//old key failed
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("原密码错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //

        ui->lineEdit_Old->clear();
        ui->lineEdit_New1->clear();
        ui->lineEdit_New2->clear();
        ui->lineEdit_Old->setFocus();
    }

}
