#include "dadmin_fbook.h"
#include "ui_dadmin_fbook.h"
#include "global_define.h"
#include "function.h"
#include "books.h"
#include <QTableWidget>
#include <fstream>
#include <string>

DAdmin_FBook::DAdmin_FBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAdmin_FBook)
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
    ui->table_Book->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_Book->setSortingEnabled(true);
    ui->table_Book->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Book->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_Book->setColumnCount(7);
    QStringList head;
    head << QString::fromLocal8Bit("ID前缀")<<QString::fromLocal8Bit("书名")<<QString::fromLocal8Bit("作者")<<QString::fromLocal8Bit("出版社")<<QString::fromLocal8Bit("类别")<<QString::fromLocal8Bit("可用数量")<<QString::fromLocal8Bit("借阅率");
    ui->table_Book->setHorizontalHeaderLabels(head);
    // table widget //
}

DAdmin_FBook::~DAdmin_FBook()
{
    delete ui;
}

void DAdmin_FBook::on_pushButton_Find_clicked()
{
    //--------------
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
    ui->table_Book->clearContents();
    ui->table_Book->setRowCount(0);

    string t, str = Convert_qstrtostr(ui->lineEdit_KeyWord->text());

    long rowcount = 0;

    fstream f("book\\booklist.txt");
    getline(f, t);

    switch (c) {
    case 1://id
        while(f.peek()!=EOF){
            getline(f, t);

            if (string::npos != t.find(str)) {//we find it
                // print this book //
                Book B(t);

                rowcount = ui->table_Book->rowCount();
                ui->table_Book->insertRow(rowcount);

                Table_Add(ui->table_Book,rowcount, 0, Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->table_Book,rowcount, 1, Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->table_Book,rowcount, 2, Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->table_Book,rowcount, 3, Convert_strtoqstr(B.get_bookpublisher()));//publisher
                Table_Add(ui->table_Book,rowcount, 4, Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->table_Book,rowcount, 5, Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num_avalibal
                Table_Add(ui->table_Book,rowcount, 6, Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use


                // print this book //
                //break;
            }
        }
        break;
    case 2://bookname
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if (string::npos != B.get_bookname().find(str)){
                // print this book //

                rowcount = ui->table_Book->rowCount();
                ui->table_Book->insertRow(rowcount);

                Table_Add(ui->table_Book,rowcount, 0, Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->table_Book,rowcount, 1, Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->table_Book,rowcount, 2, Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->table_Book,rowcount, 3, Convert_strtoqstr(B.get_bookpublisher()));//publisher
                Table_Add(ui->table_Book,rowcount, 4, Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->table_Book,rowcount, 5, Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num_avalibal
                Table_Add(ui->table_Book,rowcount, 6, Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 3://author
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if (string::npos != B.get_bookauthor().find(str)){
                // print this book //

                rowcount = ui->table_Book->rowCount();
                ui->table_Book->insertRow(rowcount);

                Table_Add(ui->table_Book,rowcount, 0, Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->table_Book,rowcount, 1, Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->table_Book,rowcount, 2, Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->table_Book,rowcount, 3, Convert_strtoqstr(B.get_bookpublisher()));//publisher
                Table_Add(ui->table_Book,rowcount, 4, Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->table_Book,rowcount, 5, Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num_avalibal
                Table_Add(ui->table_Book,rowcount, 6, Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 4://publisher
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if (string::npos != B.get_bookpublisher().find(str)){
                // print this book //

                rowcount = ui->table_Book->rowCount();
                ui->table_Book->insertRow(rowcount);

                Table_Add(ui->table_Book,rowcount, 0, Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->table_Book,rowcount, 1, Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->table_Book,rowcount, 2, Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->table_Book,rowcount, 3, Convert_strtoqstr(B.get_bookpublisher()));//publisher
                Table_Add(ui->table_Book,rowcount, 4, Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->table_Book,rowcount, 5, Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num_avalibal
                Table_Add(ui->table_Book,rowcount, 6, Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    case 5://type
        while (f.peek() != EOF) {
            getline(f, t);
            Book B(t);

            if (string::npos != B.get_booktype().find(str)){
                // print this book //

                rowcount = ui->table_Book->rowCount();
                ui->table_Book->insertRow(rowcount);

                Table_Add(ui->table_Book,rowcount, 0, Convert_strtoqstr(B.get_ID_pre()));//id
                Table_Add(ui->table_Book,rowcount, 1, Convert_strtoqstr(B.get_bookname()));//bookname
                Table_Add(ui->table_Book,rowcount, 2, Convert_strtoqstr(B.get_bookauthor()));//author
                Table_Add(ui->table_Book,rowcount, 3, Convert_strtoqstr(B.get_bookpublisher()));//publisher
                Table_Add(ui->table_Book,rowcount, 4, Convert_strtoqstr(B.get_booktype()));//type
                Table_Add(ui->table_Book,rowcount, 5, Convert_strtoqstr(Convert_longtostr(B.Num_Available)));//num_avalibal
                Table_Add(ui->table_Book,rowcount, 6, Convert_strtoqstr(Convert_doubletostr(Convert_strtodouble(FileLine_Getline("book\\"+ t + ".txt", 11))/Day)));//precent use

                // print this book //
            }
        }
        break;
    }

    f.close();
}

void DAdmin_FBook::on_pushButton_Back_clicked()
{
    uiset = 5;

    close();
}

void DAdmin_FBook::on_pushButton_clicked()
{
    uiset = 17;

    close();
}
