/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		People.cpp
			Author:		Zhang Yun
			Version:	alpha 0.91
			Intro:		everything related to 
						the people 
------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "Global_define.h"
#include "Function.h"
#include "Logbook.h"
#include "People.h"
using namespace std;


//---------------------------------------------------------------------------------
// class Person

// Ĭ�Ϲ��캯��
Person::Person() {
	Person_Notic = false;
	Person_honesty = 100;
	Person_Debt = 0.0;
	Num_Borrowed = 0;
	Num_Subscribe = 0;
}

// �������캯��
Person::Person(const Person & p1) {
	Person_Notic = p1.Person_Notic;
	Person_honesty = p1.Person_honesty;
	Person_Debt = p1.Person_Debt;
	Num_Borrowed = p1.Num_Borrowed;
	Num_Subscribe = p1.Num_Subscribe;

	Person_ID = p1.Person_ID;
	Person_Key = p1.Person_Key;
	Person_Name = p1.Person_Name;
	Person_School = p1.Person_School;
	Person_Limit = p1.Person_Limit;

}

// ���ļ������ж�ȡ
// such as Person P("000000000001");
Person::Person(const string & filename) {
	ifstream file("people\\" + filename + ".txt");

	getline(file, Person_ID);
	getline(file, Person_Key);
	getline(file, Person_Name);
	getline(file, Person_School);
	file >> Person_Limit;
	file >> Person_honesty;
	file >> Person_Debt;
	file >> Num_Borrowed;
	file >> Num_Subscribe;

	file.close();
}

// �������캯�� ���ǽ������˵ĺ��� Ҫ����ļ����д���
// ����ǰӦ�ñ�֤ID����ȷ��
Person::Person(const string & name, const string & ID, const string &Key, const string & school, const int & limit) {
	Person_Notic = false;
	Person_honesty = 100;
	Person_Debt = 0.0;
	Num_Borrowed = 0;
	Num_Subscribe = 0;
	Person_Name = name;
	Person_ID = ID;
	Person_Key = Key;
	Person_School = school;
	Person_Limit = limit;

	// update the peoplelist
	long num = Convert_strtolong(FileLine_Getline("people\\peoplelist.txt", 1));
	FileLine_Change("people\\peoplelist.txt", 1, Convert_longtostr(num + 1));
	FileLine_Insert("people\\peoplelist.txt", 1, ID);

	// create three files
	fstream f1("people\\" + ID + ".txt", fstream::out),
		f2("people\\" + ID + "_books.txt", fstream::out), 
		f3("people\\" + ID + "_subc.txt", fstream::out);

	f1 << Person_ID << endl;
	f1 << Person_Key << endl;
	f1 << Person_Name << endl;
	f1 << Person_School << endl;
	f1 << Person_Limit << endl;
	f1 << Person_honesty << endl;
	f1 << Person_Debt << endl;
	f1 << Num_Borrowed << endl;
	f1 << Num_Subscribe << endl;

	f1.close();
	f2.close();
	f3.close();

}

Person::~Person() {
}

// ���ڽ����͸�����Ϣ ���� ���˲��� ԤԼ��״ �ѽ�ͼ��
void Person::person_print() {
	cout << endl;
	cout << "������Ϣ:\n";
	cout << "ID:" << Person_ID << endl;
	cout << "����:" << Person_Name << endl;
	cout << "ѧԺ:" << Person_School << endl;
	cout << "Ȩ��:";
	if (Person_Limit == 0)
		cout << "ѧ��" << endl;
	else
		cout << "��ʦ" << endl;
	cout << "����:" << Person_honesty << endl;
	cout << "Ƿ��:" << Person_Debt << endl;

	cout << endl;
	cout << "�ѽ�ͼ��:" << Num_Borrowed << endl;
	if (Num_Borrowed > 0) {
		fstream f("people\\" + Person_ID + "_books.txt");
		string str;

		while (f.peek() != EOF) {
			getline(f, str);
			cout << "����ID:" << str << endl;
			cout << "����:" << FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2) << endl;

			getline(f, str);
			cout << "ʣ��ʱ��:" << str << endl << endl;
		}

		f.close();
	}

	cout << endl;
	cout << "ԤԼͼ��:" << Num_Subscribe << endl;
	if (Num_Subscribe > 0) {
		fstream f("people\\" + Person_ID + "_subc.txt");
		string str;

		while (f.peek() != EOF) {
			getline(f, str);
			if (8 == str.length())
				cout << "IDǰ׺: " << str << endl;
			else
				cout << "ID: " << str << endl;

			cout << "����: " << FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2) << endl;

			getline(f, str);
			cout << "״̬: ";
			if (0 == Convert_strtolong(str))
				cout << "������" << endl << endl;
			else
				cout << "����" << endl << endl;
		}

		f.close();
	}
	cout << endl;

}

//����ʵʱ��������
void Person::person_open(const string & filename) {
	ifstream file("people\\" + filename + ".txt");

	getline(file, Person_ID);
	getline(file, Person_Key);
	getline(file, Person_Name);
	getline(file, Person_School);
	file >> Person_Limit;
	file >> Person_honesty;
	file >> Person_Debt;
	file >> Num_Borrowed;
	file >> Num_Subscribe;

	file.close();
}

// ��������
void Person::person_changekey(const string & Newkey) {
	FileLine_Change("people\\" + Person_ID + ".txt", 2, Newkey);
}

string Person::get_personname() {
	return Person_Name;
}

string Person::get_personID() {
	return Person_ID;
}

string Person::get_personschool() {
	return Person_School;
}

string Person::get_personkey() {
	return Person_Key;
}

int Person::get_personlimit() {
	return Person_Limit;
}


//-------------------------------------------------------------------------
// Class ManagePeople

ManagePeople::ManagePeople() {
	Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\peoplelist.txt", 1));
}

ManagePeople::ManagePeople(const ManagePeople & M1) {
	Num_Sum_Of_People = M1.Num_Sum_Of_People;
}

ManagePeople::ManagePeople(const string & filename) {
	Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\"+filename+".txt", 1));
}

ManagePeople::~ManagePeople() {
}

// ��������ID���м�� ���ID�Ƿ����Ҫ�� ��12λ δ�ظ���
bool ManagePeople::JudgeID(const string & ID) {
	// we judge the length first
	if (12 != ID.length()) 
		return false;
	if (ID[0] != '0' && ID[0] != '1')
		return false;

	// we judge whethe the id has been used
	fstream f("people\\peoplelist.txt");

	string str;
	while (f.peek() != EOF) {
		getline(f, str);
		if (str == ID) {
			f.close();
			return false;
		}
	}

	f.close();
	return true;
}

// ��½���麯��
// �˺������ID�Ƿ��Ǵ��ڵ� �����key�Ƿ���ȷ
bool ManagePeople::JudgeKey(const string & ID, const string & Key) {
	fstream f("people\\peoplelist.txt");

	string str;
	getline(f, str);
	while (f.peek() != EOF) {
		getline(f, str);
		if (ID == str) {
			Person P(str);
			if (Key == P.get_personkey()) {
				f.close();
				return true;
			}
			else {
				f.close();
				return false;
			}
		}
	}

	f.close();

	return false;
}

//�������Ƿ����Ȿ�����ת����
bool ManagePeople::Judgesubcid(const string & bookID, const string & peopleID) {
	if (bookID.length() != 12)
		return false;
	
	fstream f("people\\" + peopleID + "_subc.txt");

	string str;
	while (f.peek() != EOF) {
		getline(f, str);
		if (str.length() == 12 && str == bookID) {
			f.close();
			return true;
		}
	}

	f.close();
	return false;
}

// �½��� Ҫ�������ID�����ǿ��еģ�����ǰ����judgeid������ 
void ManagePeople::PeopleList_Add(const string & name, const string & ID, const string &Key, const string & school, const int & limit) {
	Person P(name, ID, Key, school, limit);

	// logbook
	Logs L(Day, false);
	L.Log_Addperson(ID);
}

// ����Ƿ��
void ManagePeople::PeopleList_Pay(const string & ID) {
	FileLine_Change("people\\" + ID + ".txt", 7, "0.0");
}

// ��������
void ManagePeople::PeopleList_ChangeKey(const string & ID, const string & newkey) {
	Person P(ID);
	P.person_changekey(newkey);
}

// �������ڲ��� ����״̬�Զ��� ��ɶԸ�����Ŀ����������
void ManagePeople::PeopleList_Find() {
	cout << endl;
	cout << "�����ǲ���ѡ��:\n";
	cout << "  1:����ID\n";
	cout << "  2:��������\n";
	cout << "  3:����ѧԺ\n";
	cout << "  4:����Ȩ��\n";
	cout << "ѡ��: ";
	string str, t;
	getline(cin, str);

	while (!(1 == str.length() && ('1' <= str[0] && str[0] <= '4'))) {
		cout << "�������\n��������: ";
		getline(cin, str);
	}
	char c = str[0];

	cout << "\n ����: ";
	getline(cin, str);

	fstream f("people\\peoplelist.txt");

	getline(f, t);
	switch (c) {
	case '1':  // ID
		while (f.peek() != EOF) {
			getline(f, t);

			if (string::npos != t.find(str)) {
				Person P(t);
				P.person_print();
			}

		}
		break;
	case '2':  // name
		while (f.peek() != EOF) {
			getline(f, t);
			Person P(t);

			if (string::npos != P.get_personname().find(str)) {
				P.person_print();
			}

		}
		break;
	case '3':  // school
		while (f.peek() != EOF) {
			getline(f, t);
			Person P(t);

			if (string::npos != P.get_personschool().find(str)) {
				P.person_print();
			}

		}
		break;
	case '4':  // limit
		while (f.peek() != EOF) {
			getline(f, t);
			Person P(t);
			int i = int(Convert_strtolong(str));

			if (i == P.get_personlimit()) {
				P.person_print();
			}

		}
		break;
	}

	f.close();
}

// ÿ�µ�һ�� ˢ�������˵Ľ�����Ϣ
void ManagePeople::PeopleList_DateFlash() {
	fstream f("people\\peoplelist.txt");

	string str,t;
	getline(f, str);

	while (f.peek() != EOF) {
		// get the id
		getline(f, str);

		// change the number
		fstream f_people("people\\" + str + "_books.txt", ios::in | ios::out), f_t("logbook\\temp.txt", ios::in | ios::out|ios::trunc);

		while (f_people.peek() != EOF) {
			getline(f_people, t);
			f_t << t << endl;

			getline(f_people, t);
			long num = -1 + Convert_strtolong(t);
			f_t << Convert_longtostr(num) << endl;
		}

		f_people.close(); f_t.close();

		// rewrite the file
		f_people.open("people\\" + str + "_books.txt", ios::in | ios::out|ios::trunc);
		f_t.open("logbook\\temp.txt", ios::in | ios::out);

		while (f_t.peek() != EOF) {
			getline(f_t, t);
			f_people << t << endl;
		}

		f_people.close(); f_t.close();
	}

	f.close();
}

// ��ӡ��������Ϣ
void ManagePeople::PeopleList_Print() {
	fstream f("people\\peoplelist.txt");
	string str;

	getline(f, str);
	while (f.peek() != EOF) {
		getline(f, str);
		Person P(str);
		P.person_print();
	}

	f.close();
}
