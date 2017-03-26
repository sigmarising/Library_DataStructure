#include "duser_return.h"
#include "ui_duser_return.h"
#include "people.h"
#include "global_define.h"
#include "books.h"
#include "function.h"
#include <string>
#include <fstream>
#include <QMessageBox>

DUser_Return::DUser_Return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DUser_Return)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // table
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(3);

    QStringList head;
    head << QString::fromLocal8Bit("已借图书ID")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("剩余天数");
    ui->tableWidget->setHorizontalHeaderLabels(head);

    // sheet
    Person P(UserNow);

    long rowcount = 0;
    //borrow
    if(P.Num_Borrowed>0){
        fstream f("people\\" + UserNow + "_books.txt");
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
            Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(str));//day
        }

        f.close();
    }
    //borrow


}

DUser_Return::~DUser_Return()
{
    delete ui;
}

void DUser_Return::on_pushButton_BookReturn_clicked()
{
    string bookid=Convert_qstrtostr(ui->lineEdit_ID->text());

    if (0 == FileLine_Getnumber("people\\" + UserNow + "_books.txt", bookid)){//wrong
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("图书ID错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        ui->lineEdit_ID->clear();
        ui->lineEdit_ID->setFocus();
    }
    else{
        ManageBooks ManageB("booklist");
        ManageB.BookList_Return(bookid, UserNow);

        // MessageBox //
        QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("还书成功"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        // sheet
        Person P(UserNow);

        long rowcount = 0;
        //borrow
        if(P.Num_Borrowed>0){
            fstream f("people\\" + UserNow + "_books.txt");
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
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(str));//day
            }

            f.close();
        }
        //borrow
    }

}

void DUser_Return::on_pushButton_Return_clicked()
{
    uiset = 12;

    close();
}
