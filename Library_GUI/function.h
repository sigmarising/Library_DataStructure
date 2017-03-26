/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
            Name:		Function.h
            Author:		Zhang Yun
            Version:	alpha 0.91
            Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
#include <QString>
#include <QTableWidget>
using namespace std;

// 删除文件中的指定行
void FileLine_Delete(const string &filename, const long &line);

// 改变文件中指定行的内容
void FileLine_Change(const string &filename, const long &line, const string &things);

// 在文件的指定行之后插入内容
void FileLine_Insert(const string &filename, const long &line, const string &things);

// 将制定内容添加到文章末尾
void FileEnd_Add(const string &filename, const string &things);

// 搜索指定内容的行号（一般用于ID）
long FileLine_Getnumber(const string &filename, const string &things);

// 返回文件指定行的内容
string FileLine_Getline(const string &filename, const long &line);

// 向表格中添加单元
void Table_Add(QTableWidget *table, const int row, const int column, const QString &thing);

// str转换long
long Convert_strtolong(const string str);

// long to str
string Convert_longtostr(const long num);

// double to str
string Convert_doubletostr(const double num);

// str to double
double Convert_strtodouble(const string str);

// str to qstr
QString Convert_strtoqstr(const string str);

// qstr to str
string Convert_qstrtostr(const QString qstr);

// flash all the info
void FlashDay();
