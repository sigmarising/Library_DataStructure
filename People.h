/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		People.h
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		everything related to 
						the people 
------------------------------------------------------
				有关人的文件的存放问题
所有操作以文件交互为关键点核心，随时不把所有东西放入内存

按照同一个人一系列文件的方式进行管理，文件即日志。

所有人存放在People文件夹之下，一个人的简要信息存储一个文件
(这个文件中有个人的完整ID)；每个人借的书的信息单独存一个文件
(这个文件中每本书的完整ID)；所有预约的书存一个文件，这三个
文件构成了同一人的文件日志系统

索引文件peoplelist，里面包含已有的所有人的ID 与权限信息
------------------------------------------------------
					peoplelist格式
------------------------------------------------------
					人文件的格式
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;

// 类名: Person
// 说明: 其中包含一本书的信息 这是一个公有类
class Person
{
  public:
    Person();
    ~Person();

    bool notic;
    long honesty;
    double debt;

  private:
    string Person_ID;
    string Person_Name;
    string Person_School;

    int Person_Limit;
};
