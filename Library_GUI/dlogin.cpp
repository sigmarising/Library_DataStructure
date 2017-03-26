#include "dlogin.h"
#include "ui_dlogin.h"
#include "global_define.h"
#include "function.h"
#include "books.h"
#include "logbook.h"
#include "people.h"
#include <string>
#include <QMessageBox>

extern string UserNow;

DLogin::DLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLogin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DLogin::~DLogin()
{
    delete ui;
}

void DLogin::on_pushButton_clicked()
{
    string ID,Key;

    ID = Convert_qstrtostr(ui->lineEdit_ID->text());
    Key = Convert_qstrtostr(ui->lineEdit_Key->text());

    ManagePeople ManageP("peoplelist");
    //ManageBooks ManageB("booklist");

    Logs L(Day, false);
    if (ManageP.JudgeKey(ID, Key)){// login ok - user
        uiset = 12;
        UserNow = ID;

        //logbook
        L.Log_Login(ID);
        close();
    }
    else if ("Admin"==ID && Key == FileLine_Getline("logbook\\sys.txt",2)){// log in ok - admin

        // log book
        L.Log_Login("Admin");
        uiset = 5;

        close();
    }
    else{// login failed
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户信息错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //

        ui->lineEdit_ID->clear();
        ui->lineEdit_Key->clear();
        ui->lineEdit_ID->setFocus();
    }
}

void DLogin::on_pushButton_2_clicked()
{
    uiset = 1;

    close();
}
