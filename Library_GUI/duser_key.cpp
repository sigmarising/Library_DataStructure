#include "duser_key.h"
#include "ui_duser_key.h"
#include "people.h"
#include "global_define.h"
#include "function.h"
#include <QMessageBox>

DUser_Key::DUser_Key(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DUser_Key)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DUser_Key::~DUser_Key()
{
    delete ui;
}

void DUser_Key::on_pushButton_Change_clicked()
{
    string keyold = Convert_qstrtostr(ui->lineEdit_OldKey->text());

    ManagePeople ManageP("peoplelist");
    //ManageBooks ManageB("booklist");
    if(keyold == FileLine_Getline("people\\"+ UserNow +".txt",2)){// old key ok
        string key1 = Convert_qstrtostr(ui->lineEdit_NewKey1->text()),
                key2 =Convert_qstrtostr(ui->lineEdit_NewKey2->text());

        if(key1 == key2){
            ManageP.PeopleList_ChangeKey(UserNow, key1);
            // MessageBox //
            QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("修改成功"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //

            ui->lineEdit_OldKey->clear();
            ui->lineEdit_NewKey1->clear();
            ui->lineEdit_NewKey2->clear();
        }
        else{
            // MessageBox //
            QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("新密码不一致"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //
            ui->lineEdit_OldKey->clear();
            ui->lineEdit_NewKey1->clear();
            ui->lineEdit_NewKey2->clear();
            ui->lineEdit_OldKey->setFocus();
        }
    }
    else{
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("原密码错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        ui->lineEdit_OldKey->clear();
        ui->lineEdit_NewKey1->clear();
        ui->lineEdit_NewKey2->clear();
        ui->lineEdit_OldKey->setFocus();
    }

}

void DUser_Key::on_pushButton_Return_clicked()
{
    uiset = 12;

    close();
}
