/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	Name:		Main.cpp
	Author:		Zhang Yun
	Version:	alpha 0.8
	Intro:		use for some basic 
				farmwork's define
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#include <iostream>
#include <fstream>
#include "Books.h"
#include "People.h"
#include "Logbook.h"
#include "Function.h"
using namespace std;

// ��sys.txt ��ȡ��������
long Day = 1;				
long Num_book0 = 0;
long Num_book1 = 0;
long Num_book2 = 0;
bool Manual_Time = false;
bool Run = true;

int main() {
	/*init the file*/
	string init = FileLine_Getline("logbook\\sys.txt", 1);
	if (init == "") {
		system("md logbook");
		system("md book");
		system("md people");

		fstream f("logbook\\sys.txt",fstream::out);

		f << 1 << endl;
		f << "Admin" << endl;
		f << 0 << endl;
		f << 0 << endl;
		f << 0 << endl;
		f << 1 << endl;

		f.close();

		f.open("book\\booklist.txt", fstream::out);
		f << 0 << endl;
		f.close();

		f.open("people\\peoplelist.txt", fstream::out);
		f << 0 << endl;
		f.close();

		f.open("logbook\\temp.txt", fstream::out);
		f << 0 << endl;
		f.close();

		//FileEnd_Add("book\\booklist.txt", "0");
		//FileEnd_Add("people\\peoplelist.txt", "0");
		Logs L(Day, true);

	}
	else {
		Day =1 + Convert_strtolong(FileLine_Getline("logbook\\sys.txt", 6));
		Logs L(Day, true);
		FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));

	}

	/*++++++++++++++*/
	
	/*+++++++���������Զ���+++++++*/

	while (Run) {
		system("cls");
		cout << "��ӭ����ͼ��ݹ���ϵͳ\n\n";
		cout << "��������: " << Day << endl << endl;
		cout << "������ʲô\n";
		cout << "  1: �л���ʱ��ʽ\n";
		cout << "  2: ��½\n";
		cout << "  3: �˳�\n";
		if(Manual_Time) // �ֶ���ʱ
			cout << "  4: �ֶ�����һ��\n";
		cout << "����ѡ��: ";

		string input;
		getline(cin, input);
		char c = input[0], c1;

		if ((1 == input.length()) && (('1' <= c && c <= '3') || (Manual_Time && '4' == c)))
			switch (c) {
			case '1'://�л���ʱ��ʽ-ok
				system("cls");
				cout << "������ʲô\n";
				cout << "  1: �л��Զ���ʱ\n";
				cout << "  2: �л��ֶ���ʱ\n";
				cout << "����ѡ��: ";
				
				getline(cin, input);
				c1 = input[0];

				if ((1 == input.length()) && ('1' == c1 || '2' == c1)) {
					switch (c1) {
					case '1':
						Manual_Time = false;
						break;
					case '2':
						Manual_Time = true;
						break;
					}
					system("cls");
					cout << "�޸����" << endl;
					system("pause");
				}
				else {
					system("cls");
					cout << "��������!" << endl;
					system("pause");
				}
				break;
			case '2'://����
				login();

				break;
			case '3': // �˳�-ok
				Run = false;
				break;
			case '4'://�ֶ���һ��-ok
				// �رյ�ǰ��־�ļ����µ��ļ�
				Day += 1;

				FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));
				Logs L(Day, true);

				FlashDay();

				break;
			}
		else {
			system("cls");
			cout << "��������!" << endl;;
			system("pause");
		}

	}

	/*-------���������Զ���/*-------*/

	return 0;
}