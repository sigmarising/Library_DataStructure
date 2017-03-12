/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	Name:		Main.cpp
	Author:		Zhang Yun
	Version:	alpha 0.1
	Intro:		use for some basic 
				farmwork's define
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#include <iostream>
#include "Books.h"
#include "People.h"
#include "Logbook.h"
#include "Main_Function.h"
using namespace std;

// 从sys.txt 读取以下数据
long Day = 1;
long Num_stu = 0;
long Num_teach = 0;
long Num_book0 = 0;
long Num_book1 = 0;
long Num_book2 = 0;
bool Manual_Time = false;

int main()
{
    /*+++++++操作流程自动机+++++++*/

    while (true)
    {
        system("cls");
        cout << "欢迎来到图书馆管理系统\n\n";
        cout << "您想做什么\n";
        cout << "  1: 切换计时方式\n";
        cout << "  2: 登陆\n";
        if (Manual_Time) // 手动计时
            cout << "  3: 手动增加一天\n";
        cout << "您的选择: ";

        string input, name, key;
        getline(cin, input);
        char c = input[0];

        if ((1 == input.length()) && ('1' == c || '2' == c || '3' == c))
            switch (c)
            {
            case '1': //切换计时方式-ok
                system("cls");
                cout << "您想做什么\n";
                cout << "  1: 切换自动计时\n";
                cout << "  2: 切换手动计时\n";
                cout << "您的选择: ";

                getline(cin, input);
                char c1 = input[0];

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
                system("cls");

                cout << "请输入ID号码: ";
                getline(cin, name);
                cout << "请输入密码: ";
                getline(cin, key);

                break;
            case '3': //手动加一天
                // 关闭当前日志文件打开新的文件
                Day += 1;

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