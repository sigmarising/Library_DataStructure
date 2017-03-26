#include "dadmin_nbook1.h"
#include "ui_dadmin_nbook1.h"
#include "global_define.h"
#include "function.h"
#include "books.h"
#include <string>
#include <QMessageBox>

extern string BName,BAuthor,BPubli;

DAdmin_NBook1::DAdmin_NBook1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_NBook1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

DAdmin_NBook1::~DAdmin_NBook1()
{
    delete ui;
}

void DAdmin_NBook1::on_pushButton_clicked()
{
    //string BName,BAuthor,BPubli;

    BName = Convert_qstrtostr(ui->lineEdit_Name->text());
    BAuthor = Convert_qstrtostr(ui->lineEdit_Author->text());
    BPubli = Convert_qstrtostr(ui->lineEdit_Publisher->text());

    if(!(BName !="" && BAuthor != "" && BPubli!="")){//input null
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("以上信息不能为空"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        return;
    }

    //ManagePeople ManageP("peoplelist");
    ManageBooks ManageB("booklist");

    if(ManageB.BookList_BuyOld(BName, BAuthor, BPubli)){//already buy
        uiset =5;
        close();
    }
    else{//we need to new it
        uiset = 7;

        close();
    }
}

void DAdmin_NBook1::on_pushButton_2_clicked()
{
    uiset = 5;

    close();
}
