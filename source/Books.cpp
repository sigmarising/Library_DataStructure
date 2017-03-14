/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Books.cpp
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		everything related to 
						the Books 
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <fstream>
#include "Books.h"
#include "Function.h"
#include "Global_define.h"
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

/* 自定义构造函数 
从 filename.txt 文件中读取初始化本类书信息
filename 是本书的ID前缀（8位）
例如 Book("00000001"); */
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

/*如果新购入的书不是已有书 
那么应该创建一本新的类型的书 
ID_pre 和 Number 自动生成 并建立三个文件日志*/
Book::Book(const string &bookname, const string &bookauthor, const string &bookpublisher, const string &booktype, const int &booklimit)
{
    Num_Borrowed = Num_Subscribe = 0;
    Num_Available = Num_Sum = 1;
    // get the id and add this id
    string str = FileLine_Getline("logbook\\sys.txt", 5 + booklimit), name = "0";
    long num = Convert_strtolong(str);
    num += 1;
    str = Convert_longtostr(num);
    FileLine_Change("logbook\\sys.txt", 5 + booklimit, str);

    // creat the filename id
    name[0] = name[0] + booklimit;
    if (str.length() < 7)
        for (int i = 1; i <= 7 - str.length(); i += 1)
            name += "0";
    name += str;

    // change the booklist.txt
    string t = FileLine_Getline("book\\booklist.txt", 1);
    num = Convert_strtolong(t);
    num += 1;
    t = Convert_longtostr(num);
    FileLine_Change("book\\booklist.txt", 1, t);
    FileLine_Insert("book\\booklist.txt", num, name);

    // creat the book file
    fstream f1, f2, f3;
    f1.open("book\\" + name + ".txt");
    f2.open("book\\" + name + "_books.txt");
    f3.open("book\\" + name + "_subc.txt");

    f1 << name << endl;
    f1 << bookname << endl;
    f1 << bookauthor << endl;
    f1 << bookpublisher << endl;
    f1 << booktype << endl;
    f1 << booklimit << endl;
    f1 << 1 << endl;
    f1 << 0 << endl;
    f1 << 0 << endl;
    f1 << 1 << endl;
    f1.close();

    name += "0001"; // the "str name" now is the complete id
    f2 << name << endl;
    t = Convert_longtostr(Day);
    f2 << t << endl;
    f2 << "000000000000" << endl;
    f2 << 0 << endl;
    f2 << 100 << endl;
    f2.close();

    f3.close();
}

// 默认析构函数
Book::~Book()
{
    // nothing to do
}

// 根据 书名 作者 出版社 来判断 新输入的书是否与本类书等价
bool Book::is_equal(const string &name, const string &author, const string &publishor)
{
    if (name == Book_Name && author == Book_Author && publishor == Book_Publisher)
        return true;
    return false;
}

// 购入了一本新的书 要求更新
// <成员变量 索引文件 书表文件 预约文件>
// 预约的人可以借书时 更新人的提示信息
void Book::book_addbook()
{
    // add the total num in booklist
    Num_Sum += 1;
    long num = Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 7));
    num += 1;
    string str = Convert_longtostr(num);
    FileLine_Change("book\\" + ID_pre + ".txt", 7, str);

    // add in the ID_book.txt
    // get the total id
    string name = ID_pre, t;
    if (str.length() < 4)
        for (int i = 1; i <= 4 - str.length(); i += 1)
            name += "0";
    name += str;
    // write file
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 0, name);
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 1, Convert_longtostr(Day));
    // sovle the subcribe people
    str = FileLine_Getline("book\\" + ID_pre + "_subc.txt", 1);
    if (str != "")
    {
        FileLine_Delete("book\\" + ID_pre + "_subc.txt", 1);
        long count = 0;
        fstream f("people\\" + str + "_subc.txt");
        while (f.peek() != EOF)
        {
            count += 1;
            getline(f, t);
            if (t == ID_pre)
                break;
        }
        f.close();
        FileLine_Change("people\\" + str + "_subc.txt", count, name);
        FileLine_Change("people\\" + str + "_subc.txt", count + 1, "1");
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 2, str);
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 3, Convert_longtostr(2));
        // add the subc num
        FileLine_Change("book\\" + ID_pre + ".txt", 9, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 9))));
        Num_Subscribe += 1;
    }
    else
    {
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 2, "000000000000");
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 3, Convert_longtostr(0));
        // add the subc num
        FileLine_Change("book\\" + ID_pre + ".txt", 10, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 10))));
        Num_Available += 1;
    }
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 4, Convert_longtostr(100));
}

string Book::get_bookname()
{
    return Book_Name;
}

string Book::get_bookauthor()
{
    return Book_Author;
}

string Book::get_bookpublisher()
{
    return Book_Publisher;
}

string Book::get_booktype()
{
    return Book_Type;
}

string Book::get_ID_pre()
{
    return ID_pre;
}

int Book::get_bookLimit()
{
    return Book_Limit;
}
