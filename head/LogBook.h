/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Logbook.h
			Author:		Zhang Yun
			Version:	alpha 0.71
			Intro:		manage logbook
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include "Books.h"
#include "People.h"

class Logs
{
public:
  Logs();                              // 默认构造函数
  Logs(const long &day, bool newfile); // 建立文件
  ~Logs();                             // 析构函数 关闭文件

  void Log_Login(const string &ID);                                       // 登陆 写日志
  void Log_Logout(const string &ID);                                      // 登出 写日志
  void Log_Borrow(const string &ID_People, const string &ID_book);        // 借书 写日志
  void Log_Subscribe(const string &ID_People, const string &ID_pre_book); // 预约 写日志
  void Log_Return(const string &ID_People, const string &ID_book);        // 还书 写日志
  void Log_Addperson(const string &ID);                                   // 加人 写日志
  void Log_Addbook(const string &ID);                                     // 加书 写日志
private:
  long Date;
};
