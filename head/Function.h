/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.h
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
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

// string_addone 的辅助函数
bool Char_Addone(char &c);

// 对指定的字符串增加1 并保持字符串位置不变化
void String_Addone(string &str);

// str转换long
long Convert_strtolong(const string str);

// long to str
string Convert_longtostr(const long num);

// double to str
string Convert_doubletostr(const double num);