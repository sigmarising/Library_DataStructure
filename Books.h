/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	Name:		Books.h
	Author:		Zhang Yun
	Version:	alpha 0.1
	Intro:		everything related to 
				the Books 
---------------------------------------
		有关书的文件的存放问题
按照一本书一个文件的方式进行管理，文件即
日志。对所有书的操作使用BookManage类的方
法进行管理。

所有书存放在book文件夹之下，文件名为ID号

所有书有一个索引文件booklist，里面包含已
有的所有书的ID
---------------------------------------
		booklist格式要求
---------------------------------------
		各书日志文件格式要求
---------------------------------------
		函数的注释风格要求
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;


//	类名: Book
//	说明: Book对象表示同一本书的集合
class Book {
public:
	Book();					// 默认构造函数
	Book(const Book& B1);	// 拷贝构造函数
	~Book();				// 默认析构函数

	Book(const string &name, const string &author, const string &publisher, const string &type, const int &permmision);
	// 自定义构造函数 应该对参数的合法性进行检查 并且自动生成ID和入库时间

	string	get_ID();				// 得到ID
	string	get_Name();				// 得到书名
	string	get_Author();			// 得到作者
	string	get_Publisher();		// 得到出版社
	string	get_BuyInTime();		// 得到入库时间
	int		get_Permission();		// 得到权限值

	int	get_BorrowedTimes();						// 得到总借出次数
	int	set_BorrowedTimes(const int &new_number);	// 设置总借出次数

	int	get_Number();						// 得到可借出的等价书的数量
	int set_Number(const int &new_number);	// 设置可借出的等价书的数量

	string	get_Type();							// 得到类别
	bool	find_Type(const string &subtype);	// 查找subtype是否是本书type中的一员(子串)

	int get_state();						// 得到 当前本书状态 
	int set_state(const int &new_state);	// 设置 当前本书状态

	string get_Person();							// 得到 当前借阅者ID
	string set_Person(const string &new_person);	// 设置 当前借阅者ID

	bool judge_equal(const Book book1);		// 判断两本书是否是等价 两本书等价=>书名 作者 出版社 一致

	void print_thisbook();	// 打印本书信息
private:
	
	string ID;			// 编号	
	string Name;		// 书名	
	string Author;		// 作者
	string Publisher;	// 出版社
	string BuyInTime;	// 入库时间
	string Type;		// 类别  
						// 按照字符串格式读入 类别之间用空格区分

	int BorrowedTimes;	// 总借阅次数
	int Number;			// 可借出的等价书的数量
	
	int Permission;		// 权限  
						// 0:学生和老师  1:仅学生  2：仅老师
	
	int state;			// 状态
						// 0:未借出 1:已借出

	string Person;		// 当前借阅者的ID号(当state=1时本项可用)
};


//	类名: BookManage
//	说明: BookManage对象仅需一个 用于对所有书进行管理
class BookManage {
public:
	BookManage();		// 默认构造函数
	~BookManage();		// 析构函数


	bool BookList_Add(const string &ID);
	// 把新书的ID号添加到索引文件booklist中 并且更新所有书的等价书的数量

	int BookList_GetThisBooksNum(const string &str);
	// 根据书名来计算等价书的数量有多少本未借出

	bool File_Write(const Book &book1, const string &filename);		
	// 将book1写入文件filename中 本函数从文件头完全重写 
	// 本函数可以用于创建新书 filename要求为ID编号
	Book File_Read(const string &filename);
	// 从文件filename中读出书并以对象形式返回

	bool BookList_Find(const string &str, const int sign);
	// 从书列表中找书 要求列出所有的书
	// str为找书所输入的字符串 sign为找书方式
	// sign:
	//	1 按照ID
	//	2 按照书名
	//	3 按照出版社
	//	4 按照入库时间
	//	5 按照类型

	bool Bool_Borrow(const string &ID);
	// 根据ID号来进行借书操作 要求更新所有等价书的可借数量
private:
	
};
