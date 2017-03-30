#include "duser_borrow.h"
#include "ui_duser_borrow.h"
#include "global_define.h"
#include "books.h"
#include "people.h"
#include "function.h"
#include <string>
#include <fstream>
#include <QMessageBox>

DUser_Borrow::DUser_Borrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DUser_Borrow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // comboxitem //
    ui->comboBox_Type->addItem(QString::fromLocal8Bit("ID"));
    ui->comboBox_Type->addItem(QString::fromLocal8Bit("书名"));
    ui->comboBox_Type->addItem(QString::fromLocal8Bit("作者"));
    ui->comboBox_Type->addItem(QString::fromLocal8Bit("出版社"));
    ui->comboBox_Type->addItem(QString::fromLocal8Bit("类别"));
    // comboxitem //

    // table widget //
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setColumnCount(7);
    QStringList head;
    head << QString::fromLocal8Bit("ID前缀")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("作者")<<QString::fromLocal8Bit("出版社")<<QString::fromLocal8Bit("类别")<<QString::fromLocal8Bit("可用数量")<<QString::fromLocal8Bit("借阅率");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    // table widget //
}

DUser_Borrow::~DUser_Borrow()
{
    delete ui;
}

void DUser_Borrow::on_pushButton_Find_clicked()
{
    int c;//choose
    if(ui->comboBox_Type->currentText() == QString::fromLocal8Bit("ID"))
        c =1;
    else if(ui->comboBox_Type->currentText() == QString::fromLocal8Bit("书名"))
        c =2;
    else if(ui->comboBox_Type->currentText() == QString::fromLocal8Bit("作者"))
        c =3;
    else if(ui->comboBox_Type->currentText() == QString::fromLocal8Bit("出版社"))
        c =4;
    else if(ui->comboBox_Type->currentText() == QString::fromLocal8Bit("类别"))
        c =5;

    // clear and flash
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    string t, str = Convert_qstrtostr(ui->lineEdit_KeyWord->text());

    long rowcount = 0;

    fstream f("book\\booklist.txt");
    getline(f, t);
    Person P(UserNow);

    switch (c) {
    case 1://id
        while(f.peek()!=EOF){
            getline(f, t);

            if ((string::npos != t.find(str)) &&(t[0]=='0' || (t[0]-'1'== P.get_personlimit())) ) {//we find it
                // print this book //
                Book B(t);

                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);


                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->tableWidget,rowcount,3,Convert_strtoqstr(B.get_bookpublisher()));//publishor
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num ava
                Table_Add(ui->tableWidget,rowcount,6,Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
                //break;
            }
        }
        break;
    case 2://bookname
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if ((string::npos != B.get_bookname().find(str))&&(t[0]=='0' || (t[0]-'1'== P.get_personlimit()))){
                // print this book //

                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->tableWidget,rowcount,3,Convert_strtoqstr(B.get_bookpublisher()));//publishor
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num ava
                Table_Add(ui->tableWidget,rowcount,6,Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 3://author
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if ((string::npos != B.get_bookauthor().find(str))&&(t[0]=='0' || (t[0]-'1'== P.get_personlimit()))){
                // print this book //

                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);

                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->tableWidget,rowcount,3,Convert_strtoqstr(B.get_bookpublisher()));//publishor
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num ava
                Table_Add(ui->tableWidget,rowcount,6,Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 4://publisher
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if ((string::npos != B.get_bookpublisher().find(str))&&(t[0]=='0' || (t[0]-'1'== P.get_personlimit()))){
                // print this book //

                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);


                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->tableWidget,rowcount,3,Convert_strtoqstr(B.get_bookpublisher()));//publishor
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num ava
                Table_Add(ui->tableWidget,rowcount,6,Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 5://type
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if ((string::npos != B.get_booktype().find(str))&&(t[0]=='0' || (t[0]-'1'== P.get_personlimit()))){
                // print this book //

                rowcount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);


                Table_Add(ui->tableWidget,rowcount,0,Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->tableWidget,rowcount,1,Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->tableWidget,rowcount,2,Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->tableWidget,rowcount,3,Convert_strtoqstr(B.get_bookpublisher()));//publishor
                Table_Add(ui->tableWidget,rowcount,4,Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->tableWidget,rowcount,5,Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num ava
                Table_Add(ui->tableWidget,rowcount,6,Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    }


    f.close();
}

void DUser_Borrow::on_pushButton_Borow_clicked()
{
    string idpre = Convert_qstrtostr(ui->lineEdit_ID->text());
    ManageBooks ManageB("booklist");

    if(ManageB.JudgeIDpre(idpre)){//id ok
        if(ManageB.BookList_Borrow(idpre, UserNow, true)){


            // MessageBox //
            QMessageBox Box(QMessageBox::Information,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("借书(预约)成功"));
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
            Box.exec();
            // MessageBox //

            //reflash
            on_pushButton_Find_clicked();
        }
    }
    else{
        // MessageBox //
        QMessageBox Box(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("ID前缀错误"));
        Box.setStandardButtons(QMessageBox::Ok);
        Box.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("确认"));
        Box.exec();
        // MessageBox //
        ui->lineEdit_ID->clear();
        ui->lineEdit_ID->setFocus();
    }

}

void DUser_Borrow::on_pushButton_Return_clicked()
{
    uiset = 12;

    close();
}
