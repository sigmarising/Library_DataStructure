#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include <QString>
#include "function.h"
#include "books.h"
#include "global_define.h"
#include "logbook.h"
#include "people.h"
using namespace std;


void FileLine_Delete(const string & filename, const long & line) {
    // copy the file without the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::in | ios::out |ios::trunc); // clear this temp file
    F_file.open(filename,ios::in | ios::out);
    long count = 0;
    string str;

    while (F_file.peek() != EOF) {
        count += 1;
        getline(F_file, str);
        if (count != line)
            F_temp << str << endl;
    }

    F_temp.close();
    F_file.close();

    // rewrite in the file

    F_temp.open("logbook\\temp.txt",ios::in | ios::out);
    F_file.open(filename, ios::in | ios::out  |ios::trunc); // clear file

    while (F_temp.peek() != EOF) {
        getline(F_temp, str);
        F_file << str << endl;

    }

    F_temp.close();
    F_file.close();
}


void FileLine_Change(const string & filename, const long & line, const string & things) {
    // copy the file and change the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::in|ios::out|ios::trunc); // clear this temp file
    F_file.open(filename,ios::in | ios::out  );
    long count = 0;
    string str;

    while (F_file.peek() != EOF) {
        count += 1;
        getline(F_file, str);
        if (count != line)
            F_temp << str << endl;
        else
            F_temp << things << endl;
    }

    F_temp.close();
    F_file.close();

    // rewrite in the file

    F_temp.open("logbook\\temp.txt", ios::in | ios::out);
    F_file.open(filename, ios::in | ios::out|ios::trunc); // clear file

    while (F_temp.peek() != EOF) {
        getline(F_temp, str);
        F_file << str << endl;

    }

    F_temp.close();
    F_file.close();
}


// 0 add to the first line
void FileLine_Insert(const string & filename, const long & line, const string & things) {
    // copy the file and insert the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::in | ios::out|ios::trunc); // clear this temp file
    F_file.open(filename, ios::in | ios::out);
    long count = 0;
    if (count == line)
        F_temp << things << endl;
    string str;

    while (F_file.peek() != EOF) {
        count += 1;
        getline(F_file, str);
        F_temp << str << endl;
        if (count == line)
            F_temp << things << endl;
    }

    F_temp.close();
    F_file.close();

    // rewrite in the file

    F_temp.open("logbook\\temp.txt", ios::in | ios::out);
    F_file.open(filename, ios::in | ios::out|ios::trunc); // clear file

    while (F_temp.peek() != EOF) {
        getline(F_temp, str);
        F_file << str << endl;

    }

    F_temp.close();
    F_file.close();
}


void FileEnd_Add(const string & filename, const string & things) {
    // copy the file and insert the only 1 line
    fstream F_file;

    F_file.open(filename,ios::app);

    F_file << things << endl;

    F_file.close();
}


long FileLine_Getnumber(const string & filename, const string & things) {
    fstream F_file;

    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF) {
        count += 1;
        getline(F_file, str);
        if (str == things) {
            F_file.close();
            return count;
        }
    }

    F_file.close();
    return 0;
}


string FileLine_Getline(const string & filename, const long & line) {
    fstream F_file;

    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF) {
        count += 1;
        getline(F_file, str);
        if (count == line)
            return str;
    }

    return string();
}

// str to long
long Convert_strtolong(const string str) {
    strstream ss;
    ss << str;
    long num;
    ss >> num;
    return num;
}

// long to str
string Convert_longtostr(const long num) {
    strstream ss;
    ss << num;
    string str;
    ss >> str;
    return str;
}

// double to str
string Convert_doubletostr(const double num) {
    strstream ss;
    ss << num;
    string str;
    ss >> str;
    return str;
}

// str to double
double Convert_strtodouble(const string str) {
    strstream ss;
    ss << str;
    double num;
    ss >> num;
    return num;
}

// str to qstr
QString Convert_strtoqstr(const string str){
    QString qs;

    qs=QString::fromStdString(str);

    return qs;
}

// qstr to str
string Convert_qstrtostr(const QString qstr){
    string s;

    s=qstr.toStdString();

    return s;
}

// 向表格中添加单元
void Table_Add(QTableWidget *table, const int row, const int column, const QString &thing){
    QTableWidgetItem *item = new QTableWidgetItem(thing);

    table -> setItem(row, column, item);
}

// flash all the info
void FlashDay() {
    ManagePeople ManageP("peoplelist");
    ManageBooks ManageB("booklist");

    ManageB.BookList_DateFlash();
    ManageP.PeopleList_DateFlash();
}
