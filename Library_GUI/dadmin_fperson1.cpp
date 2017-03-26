#include "dadmin_fperson1.h"
#include "ui_dadmin_fperson1.h"
#include "global_define.h"
#include "function.h"
#include "people.h"
#include <fstream>
#include <string>

DAdmin_FPerson1::DAdmin_FPerson1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_FPerson1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // comboxitem //
    ui->comboBox->addItem(QString::fromLocal8Bit("ID"));
    ui->comboBox->addItem(QString::fromLocal8Bit("姓名"));
    ui->comboBox->addItem(QString::fromLocal8Bit("学院"));
    ui->comboBox->addItem(QString::fromLocal8Bit("学生"));
    ui->comboBox->addItem(QString::fromLocal8Bit("教师"));
    // comboxitem //

    // table widget //
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(6);
    QStringList head;
    head << QString::fromLocal8Bit("ID")<<QString::fromLocal8Bit("姓名")<<QString::fromLocal8Bit("学院")<<QString::fromLocal8Bit("权限")<<QString::fromLocal8Bit("已借书")<<QString::fromLocal8Bit("已预约");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    // table widget //
}

DAdmin_FPerson1::~DAdmin_FPerson1()
{
    delete ui;
}

void DAdmin_FPerson1::on_pushButton_2_clicked()
{
    uiset = 11;

    close();
}

void DAdmin_FPerson1::on_pushButton_3_clicked()
{
    uiset = 5;

    close();
}

void DAdmin_FPerson1::on_pushButton_clicked()
{
    //-------------
    int c, k;//c choose   k limit
    if (ui->comboBox->currentText() == QString::fromLocal8Bit("ID"))
        c = 1;
    else if (ui->comboBox->currentText() == QString::fromLocal8Bit("姓名"))
        c = 2;
    else if (ui->comboBox->currentText() == QString::fromLocal8Bit("学院"))
        c = 3;
    else if (ui->comboBox->currentText() == QString::fromLocal8Bit("学生")){
        c = 4;
        k = 0;
    }
    else if (ui->comboBox->currentText() == QString::fromLocal8Bit("教师")){
        c = 4;
        k = 1;
    }


    // clear and flash
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);


    string t, str = Convert_qstrtostr(ui->lineEdit->text());

    long rowcount = 0;

    fstream f("people\\peoplelist.txt");
    getline(f, t);

    switch (c) {
    case 1://id
        while (f.peek() != EOF) {
            getline(f, t);

            if (string::npos != t.find(str)) {
               Person P(t);
               //print the people//
               rowcount = ui->tableWidget->rowCount();
               ui->tableWidget->insertRow(rowcount);

               Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(P.get_personID()));//id
               Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr( P.get_personname()));//name
               Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(P.get_personschool()));//school
               if(0 == P.get_personlimit())
                   Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("学生"));//limit
               else
                   Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("教师"));//limit
               Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr( Convert_longtostr(P.Num_Borrowed)));//num_bor
               Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe) ));//num_sub


               //print the people//
            }

        }
        break;
    case 2://name
        while(f.peek() != EOF){
            getline(f,t);
            Person P(t);
            if (string::npos != P.get_personname().find(str)){
                //print the people//
                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(P.get_personID()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr( P.get_personname()));//name
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(P.get_personschool()));//school
                if(0 == P.get_personlimit())
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("学生"));//limit
                else
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("教师"));//limit
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr( Convert_longtostr(P.Num_Borrowed)));//num_bor
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe) ));//num_sub

                //print the people//
            }
        }
        break;
    case 3://school
        while(f.peek() != EOF){
            getline(f,t);
            Person P(t);
            if (string::npos != P.get_personschool().find(str)){
                //print the people//
                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(P.get_personID()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr( P.get_personname()));//name
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(P.get_personschool()));//school
                if(0 == P.get_personlimit())
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("学生"));//limit
                else
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("教师"));//limit
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr( Convert_longtostr(P.Num_Borrowed)));//num_bor
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe) ));//num_sub

                //print the people//
            }
        }
        break;
    case 4:
        while(f.peek() != EOF){
            getline(f,t);
            Person P(t);
            if (k == P.get_personlimit()){
                //print the people//
                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(P.get_personID()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr( P.get_personname()));//name
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(P.get_personschool()));//school
                if(0 == P.get_personlimit())
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("学生"));//limit
                else
                    Table_Add(ui->tableWidget,rowcount,3,QString::fromLocal8Bit("教师"));//limit
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr( Convert_longtostr(P.Num_Borrowed)));//num_bor
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe) ));//num_sub

                //print the people//
            }
        }
        break;
    }

    f.close();
}
