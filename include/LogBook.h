/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Logbook.h
			Author:		Zhang Yun
			Version:	alpha 0.8
			Intro:		manage logbook
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include "Books.h"
#include "People.h"

class Logs {
public:
	Logs();									// Ĭ�Ϲ��캯��
	Logs(const long &day, bool newfile);	// �����ļ�
	~Logs();								// �������� �ر��ļ�


	void Log_Login(const string &ID);			// ��½ д��־
	void Log_Logout(const string &ID);			// �ǳ� д��־
	void Log_Borrow(const string &ID_People, const string &ID_book);		// ���� д��־
	void Log_Subscribe(const string &ID_People, const string &ID_pre_book);	// ԤԼ д��־
	void Log_Return(const string &ID_People, const string &ID_book);		// ���� д��־
	void Log_Addperson(const string &ID);		// ���� д��־
	void Log_Addbook(const string &ID);			// ���� д��־
private:
	long Date;
};
