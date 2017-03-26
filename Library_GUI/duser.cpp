#include "duser.h"
#include "ui_duser.h"
#include "global_define.h"
#include "function.h"
#include "people.h"
#include "logbook.h"
#include <string>
#include <fstream>
#include <QMessageBox>

extern string UserNow;

DUser::DUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DUser)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    Person P(UserNow);

    //label
    ui->label_ID->setText(Convert_strtoqstr(P.get_personID()));
    ui->label_Name->setText(Convert_strtoqstr(P.get_personname()));
    ui->label_School->setText(Convert_strtoqstr(P.get_personschool()));
    if(0 == P.get_personlimit())
        ui->label_Limit->setText(QString::fromLocal8Bit("学生"));
    else
        ui->label_Limit->setText(QString::fromLocal8Bit("教师"));
    ui->label_Honesty->setText(Convert_strtoqstr(Convert_longtostr(P.Person_honesty)));
    ui->label_DueMoney->setText(Convert_strtoqstr(Convert_doubletostr(P.Person_Debt)));
    ui->label_Borrow->setText(Convert_strtoqstr(Convert_longtostr(P.Num_Borrowed)));
    ui->label_Subc->setText(Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe)));
    //label

    // table widget //
    ui->table_Borrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_Borrow->setSortingEnabled(true);
    ui->table_Borrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Borrow->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_Subc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_Subc->setSortingEnabled(true);
    ui->table_Subc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Subc->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_Borrow->setColumnCount(3);
    ui->table_Subc->setColumnCount(3);
    QStringList head, head2;
    head << QString::fromLocal8Bit("已借图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("剩余天数");
    ui->table_Borrow->setHorizontalHeaderLabels(head);
    head2 << QString::fromLocal8Bit("预约图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("状态");
    ui->table_Subc->setHorizontalHeaderLabels(head2);
    // table widget //

    long rowcount = 0;

    //borrow
    if(P.Num_Borrowed>0){
        fstream f("people\\" + UserNow + "_books.txt");
        string str, t;

        while(f.peek()!=EOF){
            getline(f,str);

            // sheet
            rowcount = ui->table_Borrow->rowCount();
            ui->table_Borrow->insertRow(rowcount);

            Table_Add(ui->table_Borrow,rowcount,0,Convert_strtoqstr(str));//id

            t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);
            Table_Add(ui->table_Borrow,rowcount,1,Convert_strtoqstr(t));//bookname

            getline(f,str);
            Table_Add(ui->table_Borrow,rowcount,2,Convert_strtoqstr(str));//day
        }

        f.close();
    }
    //borrow


    //subcribe
    if (P.Num_Subscribe>0){
        fstream f("people\\" + UserNow + "_subc.txt");
        string str, t;

        while(f.peek()!=EOF){
            getline(f,str);

            // sheet
            rowcount = ui->table_Subc->rowCount();
            ui->table_Subc->insertRow(rowcount);

            Table_Add(ui->table_Subc,rowcount,0,Convert_strtoqstr(str));//id

            t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);
            Table_Add(ui->table_Subc,rowcount,1,Convert_strtoqstr(t));//bookname

            getline(f,str);

            if(str == "0")
                Table_Add(ui->table_Subc,rowcount,2,QString::fromLocal8Bit("不可用"));
            else{
                Table_Add(ui->table_Subc,rowcount,2,QString::fromLocal8Bit("有书"));
                // MessageBox //
                QString mes = Convert_strtoqstr( t) + QString::fromLocal8Bit("  可以预约转借");
                QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),mes);
                Box.setStandardButtons(QMessageBox::Ok);
                Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
                Box.exec();
                // MessageBox //
            }

        }

        f.close();
    }
    //subcribe
}

DUser::~DUser()
{
    delete ui;
}

void DUser::on_pushButton_Borrow_clicked()
{
    uiset = 13;
    close();
}

void DUser::on_pushButton_Return_clicked()
{
    uiset = 14;
    close();
}

void DUser::on_pushButton_Convert_clicked()
{
    uiset = 15;
    close();
}

void DUser::on_pushButton_PayMoney_clicked()
{
    ManagePeople ManageP("peoplelist");
    ManageP.PeopleList_Pay(UserNow);
    ui->label_DueMoney->setText("0");

    // MessageBox //
    QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("还款成功"));
    Box.setStandardButtons(QMessageBox::Ok);
    Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
    Box.exec();
    // MessageBox //



}

void DUser::on_pushButton_ChangeKey_clicked()
{
    uiset = 16;

    close();
}

void DUser::on_pushButton_Logout_clicked()
{
    uiset = 1;
    Logs L(Day, false);
    L.Log_Logout(UserNow);

    close();
}
