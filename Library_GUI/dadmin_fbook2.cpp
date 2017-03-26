#include "dadmin_fbook2.h"
#include "ui_dadmin_fbook2.h"
#include "global_define.h"
#include "function.h"
#include "books.h"
#include "people.h"
#include "QMessageBox"
#include <string>
#include <fstream>

DAdmin_FBook2::DAdmin_FBook2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_FBook2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);


    // table widget //
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(5);
    QStringList head;
    head << QString::fromLocal8Bit("图书ID")<<QString::fromLocal8Bit("入库时间")<<QString::fromLocal8Bit("状态")<<QString::fromLocal8Bit("对应用户")<<QString::fromLocal8Bit("剩余天数");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    // table widget //
}

DAdmin_FBook2::~DAdmin_FBook2()
{
    delete ui;
}

void DAdmin_FBook2::on_pushButton_Find_clicked()
{
    string IDpre = Convert_qstrtostr(ui->lineEdit->text());
    ManageBooks ManageB("booklist");

    if(0 != FileLine_Getnumber("book\\booklist.txt",IDpre)){//id ok
        Book B(IDpre);

        //label
        ui->label_IDpre->setText(Convert_strtoqstr(B.get_ID_pre()));//idpre
        ui->label_Bookname->setText(Convert_strtoqstr(B.get_bookname()));//bookname
        ui->label_Author->setText(Convert_strtoqstr(B.get_bookauthor()));//author
        ui->label_Publisher->setText(Convert_strtoqstr(B.get_bookpublisher()));//publishor
        if(B.get_bookLimit() == 0)
            ui->label_Limit->setText(QString::fromLocal8Bit("无限制"));
        else if(B.get_bookLimit() == 1)
            ui->label_Limit->setText(QString::fromLocal8Bit("仅学生可借"));
        else
            ui->label_Limit->setText(QString::fromLocal8Bit("仅教师可借"));

        ui->label_NumSum->setText(Convert_strtoqstr(Convert_longtostr(B.Num_Sum)));//sum
        ui->label_NumBorr->setText(Convert_strtoqstr(Convert_longtostr(B.Num_Borrowed)));//borr
        ui->label_NumSubc->setText(Convert_strtoqstr(Convert_longtostr(B.Num_Subscribe)));//subc
        ui->label_NumAva->setText(Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//avalibal
        ui->label_Precent->setText(Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ IDpre + ".txt", 11))/Day)));//precent
        //label

        long rowcount = 0;
        string Bid,BDay,BUser,BState,BDue;

        // clear and flash
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        fstream f("book\\"+IDpre+"_books.txt");

        while(f.peek() != EOF){
            rowcount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowcount);

            getline(f, Bid);
            getline(f, BDay);
            getline(f, BUser);
            getline(f, BState);
            getline(f, BDue);

            Table_Add(ui->tableWidget,rowcount, 0, Convert_strtoqstr(Bid));//id
            Table_Add(ui->tableWidget,rowcount, 1, Convert_strtoqstr("Day "+ BDay));//buyintime

            if(BState == "0")
                Table_Add(ui->tableWidget,rowcount, 2, QString::fromLocal8Bit("空闲"));//state
            else if(BState == "1")
                Table_Add(ui->tableWidget,rowcount, 2, QString::fromLocal8Bit("已借出"));//state
            else
                Table_Add(ui->tableWidget,rowcount, 2, QString::fromLocal8Bit("已预约"));//state

            if(BUser == "000000000000")
                Table_Add(ui->tableWidget,rowcount, 3, QString::fromLocal8Bit("无"));//user
            else{
                Person P(BUser);
                Table_Add(ui->tableWidget,rowcount, 3, Convert_strtoqstr(P.get_personname()));//user
            }

            Table_Add(ui->tableWidget,rowcount, 4, Convert_strtoqstr(BDue));//dueday
        }

        f.close();
    }
    else{//id failed
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("ID前缀输入有误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //

        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }

}

void DAdmin_FBook2::on_pushButton_Back_clicked()
{
    uiset = 5;

    close();
}
