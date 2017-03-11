/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Books.h
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		everything related to 
						the Books 
------------------------------------------------------
				有关书的文件的存放问题
所有操作以文件交互为关键点核心，随时不把所有东西放入内存

按照同一本书一系列文件的方式进行管理，文件即日志。

所有书存放在book文件夹之下，一本书的简要信息存储一个文件
(这个文件中有这类书的ID前缀)；每本书的信息单独存一个文件
(这个文件中每本书的完整ID)；所有预约者存一个文件，这三个
文件构成了同一本书的集合的文件日志系统

索引文件booklist，里面包含已有的所有书的ID前缀
------------------------------------------------------
					booklist格式
------------------------------------------------------
					一类书的格式
------------------------------------------------------
				函数的注释风格要求
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;

// 类名: Item
// 说明: 其中包含一本书的信息 这是一个公有类
struct Item
{
    string ID_Book;     // 这本书的完整ID
    string ID_Borrower; // 这本书的借阅|预约者的ID
    string Time_InHub;  // 这本书的入库时间
    int Time_Due;       // 这本书的借阅剩余时间
    int state;		// 这本书的状态
			// 状态说明: 0-可借出 1-已借出 2-已预约
};

// 类名: Book
// 说明: 这是一类书的集合
// 通常我们不需要把这类书的所有信息读入内存
// 所以本类的作用是实现对一类书的相关文件进行操作
class Book
{
  public:
    Book();															       // 默认构造函数
    Book(const Book &book1);													       // 拷贝构造函数
    Book(const string &filename);												       // 自定义构造函数 从 filename.txt 文件中初始化本类书信息
    Book(const string &bookname, const string &bookauthor, const string &bookpublisher, const string &booktype, const int &booklimit); //如果新购入的书不是已有书 那么应该创建一本新的类型的书 ID_pre 和 Number 自动生成 并建立三个文件日志
    ~Book();															       // 默认析构函数

    bool is_equal(const string &name, const string &author, const string &publishor); // 根据 书名 作者 出版社 来判断 新输入的书是否与本类书等价
    bool is_subtype(const string &subtype);					      // 判断 subtype 是否为 type 的子串

    void book_addbook();			    // 购入了一本新的书 要求更新 <成员变量 索引文件 书表文件 预约文件> 预约的人可以借书时 更新人的提示信息
    void book_subscribe(const string &ID_borrower); // 增加了一个预约者 要求更新 <成员变量 索引文件 书表文件 预约文件>
    void book_convert(const string &ID_borrower);   // 将预约转换成借阅 要求更新 <成员变量 索引文件 书表文件 预约文件>
    void book_borrow(const string &ID_borrower);    // 增加了一个借阅者 要求更新 <成员变量 索引文件 书表文件 预约文件>
    void book_return(const string &ID_book);	// 还书动作相关操作 要求更新 <成员变量 索引文件 书表文件 预约文件> 预约的人可以借书时 更新人的提示信息
    void book_print();				    // 打印本书信息

    string get_bookname();      // 得到书名
    string get_bookauthor();    // 得到作者
    string get_bookpublisher(); // 得到出版社
    string get_booktype();      // 得到类别
    string get_ID_pre();	// 得到 ID 前缀
    string get_bookLimit();     // 得到权限值

    long Num_Borrowed;  // 已借出数量
    long Num_Subscribe; // 已预约数量
    long Num_Available; // 可借出数量
    long Num_Sum;       // 该书总数量
  private:
    string Book_Name;      // 书名
    string Book_Author;    // 作者名
    string Book_Publisher; // 出版社
    string Book_Type;      // 类别

    string ID_pre; // ID 前缀

    int Book_Limit; // 权限
};

// 类名: ManageBooks
// 说明: 这个类的所有成员函数都是对整套图书进行管理的系统 使用时仅需一个对象便可
class ManageBooks
{
  public:
    ManageBooks();			 // 默认构造函数
    ManageBooks(const ManageBooks &M);   // 拷贝构造函数
    ManageBooks(const string &filename); // 从filename.txt中完成读入基本信息动作
    ~ManageBooks();			 // 默认析构函数

    void BookList_Buy(const string &bookname, const string &bookauthor, const string &bookpublisher, const string &booktype, const int &booklimit); // 购入图书 读入新书信息 并要求判断 是修改现有文件还是建立新文件 booklist文件也应该被更新
    void BookList_Borrow(const string &id_pre, const string &id_person, bool Subscribe);							    // 借书 读入两个id信息 并且自动判断 进行借书动作还是预约动作(当 Subscribe 为 TRUE 时才进行预约 否则不进行预约) 借书时候自动分配完整id书
    void BookList_Return(const string &id_book, const string &id_person);									    // 根据id信息完成还书操作
    void BookList_Convert(const string &id_book, const string &id_person);									    // 根据id信息完成预约转借书操作
    void BookList_Find();															    // 本函数内部有 有限状态自动机 完成对各个项目的搜索操作

    void BookList_DateFlash(); // 每新的一天 刷新所有图书的借阅信息
    void BookList_Print();     // 打印所有书信息

    long Num_Sum_Of_Books; // 表示有多少不同种类的书
  private:
};
