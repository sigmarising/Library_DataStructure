/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.h
			Author:		Zhang Yun
			Version:	alpha 0.8
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;

// ɾ���ļ��е�ָ����
void FileLine_Delete(const string &filename, const long &line);

// �ı��ļ���ָ���е�����
void FileLine_Change(const string &filename, const long &line, const string &things);

// ���ļ���ָ����֮���������
void FileLine_Insert(const string &filename, const long &line, const string &things);

// ���ƶ�������ӵ�����ĩβ
void FileEnd_Add(const string &filename, const string &things);

// ����ָ�����ݵ��кţ�һ������ID��
long FileLine_Getnumber(const string &filename, const string &things);

// �����ļ�ָ���е�����
string FileLine_Getline(const string &filename, const long &line);

//// string_addone �ĸ�������
//bool Char_Addone(char &c);
//
//// ��ָ�����ַ�������1 �������ַ���λ�ò��仯
//void String_Addone(string &str);

// strת��long
long Convert_strtolong(const string str);

// long to str
string Convert_longtostr(const long num);

// double to str
string Convert_doubletostr(const double num);

// str to double
double Convert_strtodouble(const string str);

// login
void login();

// flash all the info
void FlashDay();
