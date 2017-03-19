/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	Name:		Main.cpp
	Author:		Zhang Yun
	Version:	alpha 0.71
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

// 从sys.txt 读取以下数据
long Day = 1;
long Num_book0 = 0;
long Num_book1 = 0;
long Num_book2 = 0;
bool Manual_Time = false;
bool Run = true;

int main()
{
    /*init the file*/
    string init = FileLine_Getline("logbook\\sys.txt", 1);
    if (init == "")
    {
	system("md logbook");
	system("md book");
	system("md people");

	fstream f("logbook\\sys.txt", fstream::out);

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
    else
    {
	Day = 1 + Convert_strtolong(FileLine_Getline("logbook\\sys.txt", 6));
	Logs L(Day, true);
	FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));
    }

    /*++++++++++++++*/

    /*+++++++操作流程自动机+++++++*/

    while (Run)
    {
	system("cls");
	cout << "欢迎来到图书馆管理系统\n\n";
	cout << "当天天数: " << Day << endl
	     << endl;
	cout << "您想做什么\n";
	cout << "  1: 切换计时方式\n";
	cout << "  2: 登陆\n";
	cout << "  3: 退出\n";
	if (Manual_Time) // 手动计时
	    cout << "  4: 手动增加一天\n";
	cout << "您的选择: ";

	string input;
	getline(cin, input);
	char c = input[0], c1;

	if ((1 == input.length()) && (('1' <= c && c <= '3') || (Manual_Time && '4' == c)))
	    switch (c)
	    {
	    case '1': //切换计时方式-ok
		system("cls");
		cout << "您想做什么\n";
		cout << "  1: 切换自动计时\n";
		cout << "  2: 切换手动计时\n";
		cout << "您的选择: ";

		getline(cin, input);
		c1 = input[0];

		if ((1 == input.length()) && ('1' == c1 || '2' == c1))
		{
		    switch (c1)
		    {
		    case '1':
			Manual_Time = false;
			break;
		    case '2':
			Manual_Time = true;
			break;
		    }
		    system("cls");
		    cout << "修改完成" << endl;
		    system("pause");
		}
		else
		{
		    system("cls");
		    cout << "输入有误!" << endl;
		    system("pause");
		}
		break;
	    case '2': //登入
		login();

		break;
	    case '3': // 退出-ok
		Run = false;
		break;
	    case '4': //手动加一天-ok
		// 关闭当前日志文件打开新的文件
		Day += 1;

		FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));
		Logs L(Day, true);

		FlashDay();

		break;
	    }
	else
	{
	    system("cls");
	    cout << "输入有误!" << endl;
	    ;
	    system("pause");
	}
    }

    /*-------操作流程自动机/*-------*/

    return 0;
}