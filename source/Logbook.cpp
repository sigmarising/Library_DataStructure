/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Logbook.cpp
			Author:		Zhang Yun
			Version:	alpha 0.71
			Intro:		manage logbook
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <iostream>
#include <fstream>
#include "Function.h"
#include "Global_define.h"
#include "Logbook.h"
using namespace std;

Logs::Logs()
{
    Date = Day;
}

// day指定当前天数
// bool为ture表示建立新文件
// bool为false表示不建立文件
Logs::Logs(const long &day, bool newfile)
{
    Date = day;

    if (newfile)
    {
        fstream f("logbook\\day" + Convert_longtostr(Date) + ".txt", fstream::out);

        f << "时间_day " << Date << endl;

        f.close();
    }
}

Logs::~Logs()
{
}

// 登陆 写日志
void Logs::Log_Login(const string &ID)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_用户登录 用户名_" + ID);
}

// 登出 写日志
void Logs::Log_Logout(const string &ID)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_用户登出 用户名_" + ID);
}

// 借书 写日志
void Logs::Log_Borrow(const string &ID_People, const string &ID_book)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_用户借阅 用户名_" + ID_People + "图书_" + ID_book);
}

// 预约 写日志
void Logs::Log_Subscribe(const string &ID_People, const string &ID_pre_book)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_用户预约 用户名_" + ID_People + "图书_" + ID_pre_book);
}

// 还书 写日志
void Logs::Log_Return(const string &ID_People, const string &ID_book)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_用户还书 用户名_" + ID_People + "图书_" + ID_book);
}

// 加人 写日志
void Logs::Log_Addperson(const string &ID)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_新建用户 用户名_" + ID);
}

// 加书 写日志
void Logs::Log_Addbook(const string &ID)
{
    FileEnd_Add("logbook\\day" + Convert_longtostr(Date) + ".txt",
                "事件_新建图书 图书_" + ID);
}
