#include "duser_convert.h"
#include "ui_duser_convert.h"
#include "global_define.h"
#include "function.h"
#include "people.h"
#include "books.h"
#include <string>
#include <fstream>
#include <QMessageBox>

DUser_Convert::DUser_Convert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DUser_Convert)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // table widget //

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(3);
    QStringList head2;

    head2 << QString::fromLocal8Bit("预约图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("状态");
    ui->tableWidget->setHorizontalHeaderLabels(head2);
    // table widget //

    // sheet
    Person P(UserNow);

    long rowcount = 0;
    //subcribe
    if (P.Num_Subscribe>0){
        fstream f("people\\" + UserNow + "_subc.txt");
        string str, t;

        while(f.peek()!=EOF){
            getline(f,str);

            // sheet
            rowcount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowcount);


            Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(str));//id

             t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);

            Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(t));//bookname


            getline(f,str);

            if(str == "0")
                Table_Add(ui->tableWidget,rowcount,2,QString::fromLocal8Bit("不可用"));//state
            else
                Table_Add(ui->tableWidget,rowcount,2,QString::fromLocal8Bit("有书"));//state
        }

        f.close();
    }
    //subcribe
}

DUser_Convert::~DUser_Convert()
{
    delete ui;
}

void DUser_Convert::on_pushButton_Borrow_clicked()
{
    string bookid = Convert_qstrtostr(ui->lineEdit_ID->text());
    ManagePeople ManageP("peoplelist");
    ManageBooks ManageB("booklist");

    if (ManageP.Judgesubcid(bookid, UserNow)){
        ManageB.BookList_Convert(bookid, UserNow);


        // MessageBox //
        QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("预约转借成功"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        // sheet
        Person P(UserNow);
        QTableWidgetItem item;
        long rowcount = 0;
        //subcribe
        if (P.Num_Subscribe>0){
            fstream f("people\\" + UserNow + "_subc.txt");
            string str, t;


            while(f.peek()!=EOF){
                getline(f,str);

                // sheet
                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);


                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(str));//id

                 t = FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2);

                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(t));//bookname


                getline(f,str);

                if(str == "0")
                    Table_Add(ui->tableWidget,rowcount,2,QString::fromLocal8Bit("不可用"));//state
                else
                    Table_Add(ui->tableWidget,rowcount,2,QString::fromLocal8Bit("有书"));//state
            }

            f.close();
        }
        //subcribe
    }
    else{
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("图书ID错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        ui->lineEdit_ID->clear();
        ui->lineEdit_ID->setFocus();
    }

}

void DUser_Convert::on_pushButton_Return_clicked()
{
    uiset = 12;

    close();
}
