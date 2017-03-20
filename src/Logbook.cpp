/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Logbook.cpp
			Author:		Zhang Yun
			Version:	alpha 0.8
			Intro:		manage logbook
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <iostream>
#include <fstream>
#include "Function.h"
#include "Global_define.h"
#include "Logbook.h"
using namespace std;

Logs::Logs() {
	Date = Day;
}

// dayָ����ǰ����
// boolΪture��ʾ�������ļ�
// boolΪfalse��ʾ�������ļ�
Logs::Logs(const long & day, bool newfile) {
	Date = day;

	if (newfile) {
		fstream f("logbook\\day" + Convert_longtostr(Date) + ".txt",fstream::out);

		f << "ʱ��_day " << Date << endl;

		f.close();
	}
}


Logs::~Logs() {
}

// ��½ д��־
void Logs::Log_Login(const string & ID) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt", 
		"�¼�_�û���¼ �û���_" + ID);
}

// �ǳ� д��־
void Logs::Log_Logout(const string & ID) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�û��ǳ� �û���_" + ID);
}

// ���� д��־
void Logs::Log_Borrow(const string & ID_People, const string & ID_book) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�û����� �û���_" + ID_People + "ͼ��_" + ID_book);
}

// ԤԼ д��־
void Logs::Log_Subscribe(const string & ID_People, const string & ID_pre_book) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�û�ԤԼ �û���_" + ID_People + "ͼ��_" + ID_pre_book);
}

// ���� д��־
void Logs::Log_Return(const string & ID_People, const string & ID_book) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�û����� �û���_" + ID_People + "ͼ��_" + ID_book);
}

// ���� д��־
void Logs::Log_Addperson(const string & ID) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�½��û� �û���_" + ID);
}

// ���� д��־
void Logs::Log_Addbook(const string & ID) {
	FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
		"�¼�_�½�ͼ�� ͼ��_" + ID);
}
