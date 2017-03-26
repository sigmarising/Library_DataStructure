#include "dadmin_nbook2.h"
#include "ui_dadmin_nbook2.h"
#include "global_define.h"
#include "function.h"
#include "books.h"
#include <string>

extern string BName,BAuthor,BPubli;

DAdmin_NBook2::DAdmin_NBook2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_NBook2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // combox
    ui->comboBox_Limit->addItem(QString::fromLocal8Bit("无限制"));
    ui->comboBox_Limit->addItem(QString::fromLocal8Bit("仅学生可借"));
    ui->comboBox_Limit->addItem(QString::fromLocal8Bit("仅教师可借"));
}

DAdmin_NBook2::~DAdmin_NBook2()
{
    delete ui;
}

void DAdmin_NBook2::on_pushButton_clicked()
{
    string BType;
    int BLimit;
    ManageBooks ManageB;

    BType = Convert_qstrtostr(ui->lineEdit_Type->text());
    if (ui->comboBox_Limit->currentText() == QString::fromLocal8Bit("无限制"))
        BLimit = 0;
    else if(ui->comboBox_Limit->currentText() == QString::fromLocal8Bit("仅学生可借"))
        BLimit = 1;
    else if(ui->comboBox_Limit->currentText() == QString::fromLocal8Bit("仅教师可借"))
        BLimit = 2;

    ManageB.BookList_BuyNew(BName, BAuthor, BPubli,BType,BLimit );

    uiset =5;
    close();
}
