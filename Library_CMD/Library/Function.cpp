/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.cpp
			Author:		Zhang Yun
			Version:	alpha 0.91
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include "Function.h"
#include "Books.h"
#include "Global_define.h"
#include "Logbook.h"
#include "People.h"
using namespace std;

/* ɾ���ļ��е�ָ����
 filename�Ǵ�·���������ļ���
 line���кţ���1��ʼ������*/
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

/* �ı��ļ���ָ���е�����
 filename �Ǵ�·���������ļ���
 line ���к� 
 things ��Ҫ�����line�е����� */
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

/* ���ļ���ָ����֮���������
 filename �Ǵ�·���������ļ���
 line ���к� 
 things ��Ҫ���뵽��line��֮������� */
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

// ���ƶ�������ӵ�����ĩβ
// filename �Ǵ�·���������ļ���
// things ��Ҫ���뵽��line��֮�������
void FileEnd_Add(const string & filename, const string & things) {
	// copy the file and insert the only 1 line
	fstream F_file;

	F_file.open(filename,ios::app);

	F_file << things << endl;

	F_file.close();
}

// ����ָ�����ݵ��кţ�һ������ID��
// ���û�������� ����0
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

/* �����ļ�ָ���е�����
 filename �Ǵ�·���������ļ���
 line ���к� 
 ���line�����򷵻ؿմ�*/
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

/* �������ַ�c����1 
 ���������λ ��ô����ture ���򷵻�false*/
//bool Char_Addone(char & c) {
//	if ('0' < c && c < '8') {
//		c += 1;
//		return false;
//	}
//	else {
//		c = '0';
//		return true;
//	}
//}

/* ��ָ�����ַ�������1 �������ַ������Ȳ��仯
 ���� str == "00000001"
 ������ִ��֮��õ� str == "00000002"*/
//void String_Addone(string & str) {
//	int pos = str.length()-1;
//	bool carry = true;
//	while (pos >= 0) {
//		if (carry)
//			if (Char_Addone(str[pos]))
//				carry = true;
//			else
//				break;
//
//		pos -= 1;
//	}
//}

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

// for the main login
void login() {
	string name, key;
	system("cls");

	// get the input
	cout << "������ID����: ";
	getline(cin, name);
	cout << "����������: ";
	getline(cin, key);

	ManagePeople ManageP("peoplelist");
	ManageBooks ManageB("booklist");
	Logs L(Day, false);
	if (ManageP.JudgeKey(name, key)) {// student and  teacher login success
		//logbook
		L.Log_Login(name);

		// print the info
		Person P(name);
		P.person_print();

		string userinput, bookidpre,subc,key1,key2;
		bool logout = false;
		while (!logout) {
			cout << "������ʲô��\n";
			cout << "  0:�鿴������Ϣ\n";
			cout << "  1:����\n";
			cout << "  2:���飨��ԤԼ��\n";
			cout << "  3:һ��������ԤԼתΪ����\n";
			cout << "  4:����\n";
			cout << "  5:����Ƿ��\n";
			cout << "  6:��������\n";
			cout << "  7:�ǳ�\n";
			cout << "ѡ��: ";
			getline(cin, userinput);
			char c = userinput[0];

			if (userinput.length() == 1 && ('0' <= c && c <= '7')) {
				switch (c) {
				case '0':// info-ok
					P.person_open(name);
					P.person_print();
					break;
				case '1':// find-ok
					ManageB.BookList_Find(1 + P.get_personlimit());
					break;
				case '2':// borrow subc-ok
					cout << "����ͼ���IDǰ׺: ";
					getline(cin, bookidpre);

					if (ManageB.JudgeIDpre(bookidpre)) {
						cout << "��������ѽ��� ���Ƿ���ԤԼ��\n  1:��\n  Other:��\n ѡ��: ";
						getline(cin, subc);
						if (subc == "1")
							ManageB.BookList_Borrow(bookidpre, name, true);
						else
							ManageB.BookList_Borrow(bookidpre, name, false);
					}
					else {
						cout << "IDǰ׺����\n";
					}
					break;
				case '3':// convert-ok
					cout << "��������ҪԤԼת���ĵ�ͼ�������ID\n input: ";
					getline(cin, bookidpre);
					if (ManageP.Judgesubcid(bookidpre, name)) {
						ManageB.BookList_Convert(bookidpre, name);
					}
					else {
						cout << "����ID����\n";
					}
					break;
				case '4':// return book
					// we use key1 for the book we want to return
					cout << "����Ҫ���������ID: ";
					getline(cin, key1);
					if (0 == FileLine_Getnumber("people\\" + name + "_books.txt", key1)) {
						cout << "ID����" << endl;
					}
					else {
						ManageB.BookList_Return(key1, name);
					}


					break;
				case '5':// payback-ok
					ManageP.PeopleList_Pay(name);
					break;
				case '6'://change key-ok
					cout << "����������: ";
					getline(cin, key1);
					cout << "������һ��: ";
					getline(cin, key2);
					while (key1 != key2) {
						cout << "�������벻һ�£��������룡" << endl;
						cout << "����������: ";
						getline(cin, key1);
						cout << "������һ��: ";
						getline(cin, key2);
					}
					ManageP.PeopleList_ChangeKey(name, key1);

					break;
				case '7':// logout-ok
					logout = true;

					//logbook
					L.Log_Logout(name);
					break;
				}
			}
			else {
				cout << "�������\n";
			}
		}
	}
	else if ("Admin"==name && key == FileLine_Getline("logbook\\sys.txt",2)) {// the admin login succeed
		bool logout = false;
		//logbook
		L.Log_Login("Admin");

		while (!logout) {
			cout << "������ʲô��\n";
			cout << "  1:�½�ͼ��\n";
			cout << "  2:�½��û�\n";
			cout << "  3:����\n";
			cout << "  4:����\n";
			cout << "  5:�ǳ�\n";
			cout << "ѡ��: ";
			string userinput, bookname, bookauthor, bookpublishor, booktype;
			string peopleid, peoplekey, peoplename, peopleschool;
			int booklimit, peoplelimit;
			getline(cin, userinput);
			char c = userinput[0];

			if (userinput.length() == 1 && ('1' <= c && c <= '5')) {
				switch (c) {
				case '1':// new book-ok
					cout << "������ͼ����Ϣ\n";
					cout << "����:";
					getline(cin, bookname);
					cout << "����:";
					getline(cin, bookauthor);
					cout << "������:";
					getline(cin, bookpublishor);

					if (ManageB.BookList_BuyOld(bookname, bookauthor, bookpublishor)) {
						break;
					}

					cout << "���:";
					getline(cin, booktype);
					cout << "Ȩ�ޣ�0���ɽ� 1��ѧ���ɽ� 2����ʦ�ɽ裩:";
					cin >> booklimit;
					while (!(0 <= booklimit&&booklimit <= 2)) {
						cout << "��������\n��������:";
						cin >> booklimit;
					}
					getchar();

					ManageB.BookList_BuyNew(bookname, bookauthor, bookpublishor, booktype, booklimit);

					break;
				case '2'://new user-ok
					cout << "�����û���Ϣ\n";
					cout << "�û�ID��12λ ��λ��0��1��:";
					getline(cin, peopleid);
					while (!ManageP.JudgeID(peopleid)) {
						cout << "ID����\n��������:";
						getline(cin, peopleid);
					}
					cout << "�û�����:";
					getline(cin, peoplekey);
					cout << "�û�����:";
					getline(cin, peoplename);
					cout << "�û�ѧԺ:";
					getline(cin, peopleschool);
					cout << "�û�Ȩ�ޣ�0ѧ�� 1��ʦ��:";
					cin >> peoplelimit;
					while (!(0 <= peoplelimit&&peoplelimit <= 1)) {
						
						cout << "��������\n��������:";
						cin >> peoplelimit;
					}
					getchar();

					ManageP.PeopleList_Add(peoplename, peopleid, peoplekey, peopleschool, peoplelimit);

					break;
				case '3'://find book-ok

					cout << "�Ƿ�鿴�����飿\n  1:��\n  Other:��\nѡ��: ";
					getline(cin, userinput);

					if (userinput == "1") {
						ManageB.BookList_Print();
					}
					else
						ManageB.BookList_Find(3);

					break;
				case '4'://find people-ok
					cout << "�Ƿ�鿴�����û���\n  1:��\n  Other:��\nѡ��: ";
					getline(cin, userinput);

					if (userinput == "1") {
						ManageP.PeopleList_Print();
					}
					else
						ManageP.PeopleList_Find();

					break;
				case '5'://logout
					logout = true;

					// logbook
					Logs L(Day, false);
					L.Log_Logout("Admin");

					break;
				}
			}
			else {
				cout << "�������룡 \n";
			}
		}
	}
	else {//login failed
		system("cls");
		cout << "��¼ʧ��" << endl;
		system("pause");
	}
}

// flash all the info
void FlashDay() {
	ManagePeople ManageP("peoplelist");
	ManageBooks ManageB("booklist");

	ManageB.BookList_DateFlash();
	ManageP.PeopleList_DateFlash();
}
