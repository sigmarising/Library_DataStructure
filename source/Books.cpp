/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Books.cpp
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		everything related to 
						the Books 
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <fstream>
#include "Books.h"
using namespace std;

// 默认构造函数
Book::Book()
{
    Num_Borrowed = Num_Subscribe = Num_Available = Num_Sum = 0;

    Book_Limit = 0;
}

// 拷贝构造函数
Book::Book(const Book &book1)
{
    Num_Available = book1.Num_Available;
    Num_Borrowed = book1.Num_Borrowed;
    Num_Subscribe = book1.Num_Subscribe;
    Num_Sum = book1.Num_Sum;

    Book_Author = book1.Book_Author;
    Book_Limit = book1.Book_Limit;
    Book_Name = book1.Book_Name;
    Book_Publisher = book1.Book_Publisher;
    Book_Type = book1.Book_Type;

    ID_pre = book1.ID_pre;
}

// 自定义构造函数
// 从 filename.txt 文件中读取初始化本类书信息
// filename 是本书的ID前缀（8位）
// 例如 Book("00000001");
Book::Book(const string &filename)
{
    ifstream file("book\\" + filename + ".txt");

    string temp;

    getline(file, ID_pre);
    getline(file, Book_Name);
    getline(file, Book_Author);
    getline(file, Book_Publisher);
    getline(file, Book_Type);
    file >> Book_Limit;
    file >> Num_Sum;
    file >> Num_Borrowed;
    file >> Num_Subscribe;
    file >> Num_Available;

    file.close();
}

//如果新购入的书不是已有书
//那么应该创建一本新的类型的书
//ID_pre 和 Number 自动生成 并建立三个文件日志
//--------------------本函数未写完
Book::Book(const string &bookname, const string &bookauthor, const string &bookpublisher, const string &booktype, const int &booklimit)
{
    // get the id and add this id
    fstream file("logbook\\sys.txt");
    string temp;
    long id;
    for (int i = 1; i <= 4 + booklimit; i += 1)
        getline(file, temp);
    file >> id;
}
