#include "dadmin_fperson2.h"
#include "ui_dadmin_fperson2.h"
#include "global_define.h"
#include "people.h"
#include "function.h"
#include <string>
#include <fstream>
#include <QMessageBox>

DAdmin_FPerson2::DAdmin_FPerson2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_FPerson2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // table widget //
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSortingEnabled(true);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget_2->setColumnCount(3);
    QStringList head, head2;
    head << QString::fromLocal8Bit("已借图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("剩余天数");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    head2 << QString::fromLocal8Bit("预约图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("状态");
    ui->tableWidget_2->setHorizontalHeaderLabels(head2);
    // table widget //
}

DAdmin_FPerson2::~DAdmin_FPerson2()
{
    delete ui;
}

void DAdmin_FPerson2::on_pushButton_Back_clicked()
{
    uiset = 5;

    close();
}

void DAdmin_FPerson2::on_pushButton_Find_clicked()
{
    string PID = Convert_qstrtostr(ui->lineEdit_InputID->text());
    ManagePeople ManageP("peoplelist");
    if(0!=FileLine_Getnumber("people\\peoplelist.txt",PID)){//id ok
        Person P(PID);

        //label
        ui->label_ID->setText(Convert_strtoqstr(P.get_personID()));
        ui->label_Key->setText(Convert_strtoqstr(FileLine_Getline("people\\"+PID+".txt",2)));
        ui->label_Name->setText(Convert_strtoqstr(P.get_personname()));
        ui->label_School->setText(Convert_strtoqstr(P.get_personschool()));
        if(0 == P.get_personlimit())
            ui->label_Limit->setText(QString::fromLocal8Bit("学生"));
        else
            ui->label_Limit->setText(QString::fromLocal8Bit("教师"));
        ui->label_Honesty->setText(Convert_strtoqstr(Convert_longtostr(P.Person_honesty)));
        ui->label_DueMoney->setText(Convert_strtoqstr(Convert_doubletostr(P.Person_Debt)));
        ui->label_NumBor->setText(Convert_strtoqstr(Convert_longtostr(P.Num_Borrowed)));
        ui->label_NumSub->setText(Convert_strtoqstr(Convert_longtostr(P.Num_Subscribe)));
        //label


        long rowcount = 0;

        // clear and flash
        ui->tableWidget->clearContents();
        ui->tableWidget_2->clearContents();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget_2->setRowCount(0);



        //borrow
        if(P.Num_Borrowed>0){
            fstream f("people\\" + PID + "_books.txt");
            string str, t;

            while(f.peek()!=EOF){
                getline(f,str);

                // sheet
                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(str));//id
                t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(t)); //bookname

                getline(f,str);
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(str));//day
            }

            f.close();
        }
        //borrow


        //subcribe
        if (P.Num_Subscribe>0){
            fstream f("people\\" + PID + "_subc.txt");
            string str, t;

            while(f.peek()!=EOF){
                getline(f,str);

                // sheet
                rowcount = ui->tableWidget_2->rowCount();
                ui->tableWidget_2->insertRow(rowcount);


                Table_Add(ui->tableWidget_2,rowcount,0,Convert_strtoqstr(str));//id

                t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);
                Table_Add(ui->tableWidget_2,rowcount,1,Convert_strtoqstr(t));//bookname

                getline(f,str);

                if(str == "0")
                    Table_Add(ui->tableWidget_2,rowcount,2,QString::fromLocal8Bit("不可用"));
                else
                    Table_Add(ui->tableWidget_2,rowcount,2,QString::fromLocal8Bit("有书"));
            }

            f.close();
        }
        //subcribe
    }
    else{
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户ID输入有误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        ui->lineEdit_InputID->clear();
        ui->lineEdit_InputID->setFocus();
    }

}
