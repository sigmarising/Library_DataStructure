#include "dadmin_nperson.h"
#include "ui_dadmin_nperson.h"
#include "global_define.h"
#include "people.h"
#include "function.h"
#include <string>
#include <QMessageBox>

DAdmin_NPerson::DAdmin_NPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_NPerson)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    ui->comboBox_Limit->addItem(QString::fromLocal8Bit("学生"));
    ui->comboBox_Limit->addItem(QString::fromLocal8Bit("教师"));
}

DAdmin_NPerson::~DAdmin_NPerson()
{
    delete ui;
}

void DAdmin_NPerson::on_pushButton_clicked()
{
    string PID = Convert_qstrtostr(ui->lineEdit_ID->text());

    ManagePeople ManageP;

    if(ManageP.JudgeID(PID)){//id ok
        string PName, PKey, PSchool;
        int PLimit;

        PName = Convert_qstrtostr(ui->lineEdit_Name->text());
        PKey = Convert_qstrtostr(ui->lineEdit_Key->text());
        PSchool = Convert_qstrtostr(ui->lineEdit_School->text());

        if(!(PName!="" && PKey!="" && PSchool!="")){
            // MessageBox //
            QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("以上信息不能为空"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //
            return;
        }


        if(ui->comboBox_Limit->currentText() == QString::fromLocal8Bit("学生"))
            PLimit = 0;
        else if(ui->comboBox_Limit->currentText() ==QString::fromLocal8Bit( "教师"))
            PLimit =1;

        //ManageP.PeopleList_Add(peoplename, peopleid, peoplekey, peopleschool, peoplelimit);
        ManageP.PeopleList_Add(PName,PID,PKey,PSchool,PLimit);

        uiset = 5;
        close();
    }
    else{// id wrong
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户ID输入有误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();

        ui->lineEdit_ID->clear();
        ui->lineEdit_ID->setFocus();
        // MessageBox //
    }
}

void DAdmin_NPerson::on_pushButton_2_clicked()
{
    uiset = 5;

    close();
}
