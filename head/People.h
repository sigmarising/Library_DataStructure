/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		People.h
			Author:		Zhang Yun
			Version:	alpha 0.6
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
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;

// 类名: Person
// 说明: 其中包含一个人的信息合操作
class Person
{
public:
  Person();                                                                                                // 默认构造函数
  Person(const Person &p1);                                                                                // 拷贝构造函数
  Person(const string &filename);                                                                          // 从文件名进行读取
  Person(const string &name, const string &ID, const string &Key, const string &school, const int &limit); // 参数构造函数 这是建立新人的函数 要求对文件进行创建
  ~Person();                                                                                               // 默认析构函数

  void person_print(); // 用于将发送个人信息 包括 个人参数 预约现状 已借图书
  //void person_findbook();							// 用于查找图书 查找图书可以根据ID 书名 作者 出版社 类别 来进行
  //void person_borrow(const string &ID_pre_book);	// 根据图书的ID前缀完成借书操作 修改自身的文件日志
  //void person_return(const string &ID_book);		// 根据图书的完整ID完成还书操作 修改自身的文件日志
  //void person_convert();							// 将预约的书转换成已借的书 修改自身的文件日志
  void person_changekey(const string &Newkey); // 更改密码

  string get_personname();   // 获取个人名字
  string get_personID();     // 获取个人ID
  string get_personschool(); // 获取个人学院
  string get_personkey();    // 获取个人密码
  int get_personlimit();     // 获取个人权限

  bool Person_Notic;   // 是否发送通知
  long Person_honesty; // 诚信度 默认100
  double Person_Debt;  // 欠款 默认0.0
  long Num_Borrowed;   // 已借阅数量
  long Num_Subscribe;  // 已预约数量
private:
  string Person_ID;     // 个人ID
  string Person_Key;    // 个人登录密码
  string Person_Name;   // 个人姓名
  string Person_School; // 个人学院

  int Person_Limit; // 个人权限 0学生 1老师
};

// 类名: ManagePeople
// 说明: 这个类用于对人进行管理

class ManagePeople
{
public:
  ManagePeople();                       // 默认构造函数
  ManagePeople(const ManagePeople &M1); // 拷贝构造函数
  ManagePeople(const string &filename); // 从文件名读取来初始化信息
  ~ManagePeople();                      // 默认析构函数

  bool JudgeID(const string &ID);                                 // 本函数对ID进行检测 检测ID是否符合要求 （12位 未重复）
  bool JudgeKey(const string &ID, const string &Key);             // 登陆检验函数
  bool Judgesubcid(const string &bookID, const string &peopleID); //检验人是否有这本书可以转借阅

  void PeopleList_Add(const string &name, const string &ID, const string &Key, const string &school, const int &limit); // 新建人 要求给定的ID必须是可行的（可先前利用judgeid函数）

  // 借书还书转换的操作通过ManageBook来实现 即ManageBook实现对书和人的文件日志的共同操作

  void PeopleList_Find(); // 本函数内部有 有限状态自动机 完成对各个项目的搜索操作

  void PeopleList_DateFlash(); // 每新的一天 刷新所有人的借阅信息
  void PeopleList_Print();     // 打印所有人信息

  long Num_Sum_Of_People;

private:
};
