#include <iostream>
#include <fstream>
#include "books.h"
#include "logbook.h"
#include "function.h"
#include "global_define.h"
#include <QMessageBox>
using namespace std;


//--------------------------------------------------------------------
//Class Book



Book::Book() {
    Num_Borrowed = Num_Subscribe = Num_Available = Num_Sum = 0;

    Book_Limit = 0;
}


Book::Book(const Book & book1) {
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


Book::Book(const string & filename) {
    ifstream file("book\\" + filename + ".txt");

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


Book::Book(const string & bookname, const string & bookauthor, const string & bookpublisher, const string & booktype, const int & booklimit) {
    Num_Borrowed = Num_Subscribe =  0;
    Num_Available = Num_Sum = 1;
    // get the id and add this id
    string str = FileLine_Getline("logbook\\sys.txt", 3 + booklimit), name="0";
    long num = Convert_strtolong(str);
    num += 1;
    str = Convert_longtostr(num);
    FileLine_Change("logbook\\sys.txt", 3 + booklimit, str);

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
    f1.open("book\\"+name+".txt", fstream::out);
    f2.open("book\\" + name+"_books.txt", fstream::out);
    f3.open("book\\" +name+ "_subc.txt", fstream::out);

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
    f1 << 0 << endl;
    f1.close();

    name += "0001";// the "str name" now is the complete id

    //logbook
    Logs L(Day, false);
    L.Log_Addbook(name);

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
Book::~Book() {
    // nothing to do
}

// 根据 书名 作者 出版社 来判断 新输入的书是否与本类书等价
bool Book::is_equal(const string & name, const string & author, const string & publishor) {
    if (name == Book_Name && author == Book_Author && publishor == Book_Publisher)
        return true;
    return false;
}

// 购入了一本新的书 要求更新
// <成员变量 索引文件 书表文件 预约文件>
// 预约的人可以借书时 更新人的提示信息
void Book::book_addbook() {
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

    // logbook
    Logs L(Day, false);
    L.Log_Addbook(name);

    // write file part 1(2)
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 0, name);
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 1, Convert_longtostr(Day));
    // sovle the subcribe people
    str = FileLine_Getline("book\\" + ID_pre + "_subc.txt", 1);
    if (str != "") {
        FileLine_Delete("book\\" + ID_pre + "_subc.txt", 1);
        long count = FileLine_Getnumber("people\\" + str + "_subc.txt",ID_pre);

        FileLine_Change("people\\" + str + "_subc.txt", count, name);
        FileLine_Change("people\\" + str + "_subc.txt", count + 1, "1");
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 2, str);//str is people id
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 3, "2");
        // add the subc num
        FileLine_Change("book\\" + ID_pre + ".txt", 9, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 9))));
        Num_Subscribe += 1;
    }
    else {
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 2, "000000000000");
        FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 3, "0");
        // add the subc num
        FileLine_Change("book\\" + ID_pre + ".txt", 10, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 10))));
        Num_Available += 1;
    }
    FileLine_Insert("book\\" + ID_pre + "_books.txt", (num - 1) * 5 + 4, "100");

}

// 增加了一个预约者 (此时应该已经判断出来应该是要预约 因为已经没书可借)
// 要求更新 <成员变量 索引文件 书表文件 预约文件>
void Book::book_subscribe(const string & ID_borrower) {
    // update the ID_subc.txt 应该插入到到末行
    //FileLine_Insert("book\\" + ID_pre + "_subc.txt", 0, ID_borrower);
    FileEnd_Add("book\\" + ID_pre + "_subc.txt", ID_borrower);

    // update the file about people
    FileLine_Change("people\\" + ID_borrower + ".txt", 9, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("people\\"+ID_borrower + ".txt", 9))));
    FileLine_Insert("people\\" + ID_borrower + "_subc.txt", 0, ID_pre);
    FileLine_Insert("people\\" + ID_borrower + "_subc.txt", 1, "0");

    // logbook
    Logs L(Day, false);
    L.Log_Subscribe(ID_borrower, ID_pre);
}

// 将预约转换成借阅 (此时这个人应该不在预约队列中了 已经有书被预约给他了)
// 要求更新 <成员变量 索引文件 书表文件 预约文件>
void Book::book_convert(const string & ID_book, const string & ID_borrower) {
    // we get the complete id from the ID_Borrower

    long count = FileLine_Getnumber("people\\" + ID_borrower + "_subc.txt", ID_book);

    // delete the subc info in the people's subc file
    FileLine_Delete("people\\" + ID_borrower + "_subc.txt", count);
    FileLine_Delete("people\\" + ID_borrower + "_subc.txt", count);
    // add the borrow info in the people book file and change the people.txt
    FileLine_Change("people\\" + ID_borrower + ".txt", 8, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 8))));
    FileLine_Change("people\\" + ID_borrower + ".txt", 9, Convert_longtostr(-1 + Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 9))));

    FileEnd_Add("people\\" + ID_borrower + "_books.txt", ID_book);
    FileEnd_Add("people\\" + ID_borrower + "_books.txt", "30");

    // update the booksfile
    long lnum = FileLine_Getnumber("book\\" + ID_pre + "_books.txt", ID_book);
    FileLine_Change("book\\" + ID_pre + "_books.txt", lnum + 2, ID_borrower);
    FileLine_Change("book\\" + ID_pre + "_books.txt", lnum + 3, "1");
    FileLine_Change("book\\" + ID_pre + "_books.txt", lnum + 4, "30");

    FileLine_Change("book\\" + ID_pre + ".txt", 8, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 8))));
    FileLine_Change("book\\" + ID_pre + ".txt", 9, Convert_longtostr(-1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 9))));
    FileLine_Change("book\\" + ID_pre + ".txt", 11, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 11))));

    // update the member var
    Num_Borrowed += 1;
    Num_Subscribe -= 1;

    // logbook
    Logs L(Day, false);
    L.Log_Convert(ID_borrower,ID_book);
}

// 增加了一个借阅者
// 要求更新 <成员变量 索引文件 书表文件 预约文件>
void Book::book_borrow(const string & ID_borrower) {
    // we check the limit there-----------
    int limit_person = int(Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 5)));

    if (0 == limit_person) {
        if (!(0 == Book_Limit || 1 == Book_Limit)) {
            // MessageBox //
            QMessageBox Box(QMessageBox::Warning,"警告","您没有权限借阅此书");
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,"确认");
            Box.exec();
            // MessageBox //
            return;
        }
    }
    else if (1 == limit_person) {
        if (!(0 == Book_Limit || 2 == Book_Limit)) {
            // MessageBox //
            QMessageBox Box(QMessageBox::Warning,"警告","您没有权限借阅此书");
            Box.setStandardButtons(QMessageBox::Ok);
            Box.setButtonText(QMessageBox::Ok,"确认");
            Box.exec();
            // MessageBox //
            return;
        }
    }

    // we check the limit there-----------

    // update the member var and change the ID.txt
    Num_Borrowed += 1;
    Num_Available -= 1;
    FileLine_Change("book\\" + ID_pre + ".txt", 8, Convert_longtostr(Num_Borrowed));
    FileLine_Change("book\\" + ID_pre + ".txt", 10, Convert_longtostr(Num_Available));
        // 借阅率
    FileLine_Change("book\\" + ID_pre + ".txt", 11, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 11))));


    // find one avaliable book and remember the linenumber of it
    fstream F("book\\" + ID_pre + "_books.txt");
    string str;

    long linenumber = 0;
    while (F.peek() != EOF) {
        for (int i = 1; i <= 4; i += 1) {
            getline(F, str);
            linenumber += 1;
        }
        if (0 == Convert_strtolong(str))
            break;
        else {
            getline(F, str);
            linenumber += 1;
        }
    }
    F.close();

    // update the ID_Books.txt
    FileLine_Change("book\\" + ID_pre + "_books.txt", linenumber - 1, ID_borrower);
    FileLine_Change("book\\" + ID_pre + "_books.txt", linenumber , "1");
    FileLine_Change("book\\" + ID_pre + "_books.txt", linenumber + 1, "30");


    // update the file about people
    FileLine_Change("people\\" + ID_borrower + ".txt", 8, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 8))));
    FileEnd_Add("people\\" + ID_borrower + "_books.txt", FileLine_Getline("book\\" + ID_pre + "_books.txt", linenumber - 3));
    FileEnd_Add("people\\" + ID_borrower + "_books.txt", "30");

    // logbook
    Logs L(Day, false);
    L.Log_Borrow(ID_borrower, FileLine_Getline("people\\" + ID_pre + "_books.txt", linenumber - 3));
}

// 还书动作相关操作
// 要求更新 <成员变量 索引文件 书表文件 预约文件>
// 预约的人可以借书时 更新人的提示信息
void Book::book_return(const string & ID_book, const string & ID_borrower) {
    // we need to return the book and get the subc people for the book
    // so we judge it first
        // get the subc people ID in str
    string str = FileLine_Getline("book\\" + ID_pre + "_subc.txt", 1);
    if ("" != str) {//we have at least one subc people
        FileLine_Delete("book\\" + ID_pre + "_subc.txt", 1);
        // file about book
        long num = FileLine_Getnumber("book\\" + ID_pre + "_books.txt", ID_book);
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 2, str);// str is the people id
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 3, "2");
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 4, "100");

        Num_Borrowed -= 1;
        Num_Subscribe += 1;

        FileLine_Change("book\\" + ID_pre + ".txt", 8, Convert_longtostr(-1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 8))));
        FileLine_Change("book\\" + ID_pre + ".txt", 9, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 9))));
        // file about people subc
        num = FileLine_Getnumber("people\\" + str + "_subc.txt", ID_pre);
        FileLine_Change("people\\" + str + "_subc.txt", num, ID_book);
        FileLine_Change("people\\" + str + "_subc.txt", num + 1, "1");
    }
    else {// we don't have to solve the subc because there is no subc people
        long num = FileLine_Getnumber("book\\" + ID_pre + "_books.txt", ID_book);
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 2, "000000000000");
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 3, "0");
        FileLine_Change("book\\" + ID_pre + "_books.txt", num + 4, "100");

        Num_Borrowed -= 1;
        Num_Available += 1;

        FileLine_Change("book\\" + ID_pre + ".txt", 8, Convert_longtostr(-1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 8))));
        FileLine_Change("book\\" + ID_pre + ".txt", 10, Convert_longtostr(1 + Convert_strtolong(FileLine_Getline("book\\" + ID_pre + ".txt", 10))));
    }
    // solve the money
    long line = FileLine_Getnumber("people\\" + ID_borrower + "_books.txt", ID_book);
    FileLine_Delete("people\\" + ID_borrower + "_books.txt", line);
    long dueday = Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + "_books.txt", line));
    FileLine_Delete("people\\" + ID_borrower + "_books.txt", line);

    if(dueday<0){
        FileLine_Change("people\\" + ID_borrower + ".txt", 6, Convert_longtostr(dueday + Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 6))));
        FileLine_Change("people\\" + ID_borrower + ".txt", 7, Convert_doubletostr(0.1*(-dueday) + Convert_strtodouble(FileLine_Getline("people\\" + ID_borrower + ".txt", 7))));
    }
    FileLine_Change("people\\" + ID_borrower + ".txt", 8, Convert_longtostr(-1 + Convert_strtolong(FileLine_Getline("people\\" + ID_borrower + ".txt", 8))));

}


string Book::get_bookname() {
    return Book_Name;
}

string Book::get_bookauthor() {
    return Book_Author;
}

string Book::get_bookpublisher() {
    return Book_Publisher;
}

string Book::get_booktype() {
    return Book_Type;
}

string Book::get_ID_pre() {
    return ID_pre;
}

int Book::get_bookLimit() {
    return Book_Limit;
}

//-------------------------------------------------------------------
// class ManageBooks

ManageBooks::ManageBooks() {
    Num_Sum_Of_Books = Convert_strtolong(FileLine_Getline("book\\booklist.txt", 1));
}

ManageBooks::ManageBooks(const ManageBooks & M) {
    Num_Sum_Of_Books = M.Num_Sum_Of_Books;
}

ManageBooks::ManageBooks(const string & filename) {
    Num_Sum_Of_Books = Convert_strtolong(FileLine_Getline("book\\" + filename + ".txt", 1));
}

ManageBooks::~ManageBooks() {
}

// 判断idpre是否是存在的
bool ManageBooks::JudgeIDpre(const string & idpre) {
    fstream f("book\\booklist.txt");

    string str;
    getline(f, str);
    while (f.peek() != EOF) {
        getline(f, str);
        if (idpre == str) {
            f.close();
            return true;
        }
    }

    f.close();
    return false;
}

// 首先判断是否存在这样的书
// 如果有 那么 购入图书 读入新书信息
// 修改现有文件 booklist文件也应该被更新 返回true
// 如果没有 返回false
bool ManageBooks::BookList_BuyOld(const string & bookname, const string & bookauthor, const string & bookpublisher) {
    fstream f("book\\booklist.txt");

    string str;
    while (f.peek() != EOF) {
        getline(f, str);
        Book B(str);
        if (B.is_equal(bookname, bookauthor, bookpublisher)) {
            B.book_addbook();
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

// buy book
void ManageBooks::BookList_BuyNew(const string & bookname, const string & bookauthor, const string & bookpublisher, const string & booktype, const int & booklimit) {
    Book B(bookname, bookauthor, bookpublisher, booktype, booklimit);
}

// borrow book
void ManageBooks::BookList_Borrow(const string & id_pre, const string & id_person, bool Subscribe) {
    long num = Convert_strtolong(FileLine_Getline("book\\" + id_pre + ".txt", 10));
    Book B( id_pre );

    if (num >= 1) {// we can lent it
        B.book_borrow(id_person);
    }
    else {// we don't have avabliable book
        if (Subscribe)
            B.book_subscribe(id_person);
    }
}

// return book
void ManageBooks::BookList_Return(const string & id_book, const string & id_person) {
    string id_pre = id_book;
    id_pre = id_pre.substr(0, 8);

    Book B(id_pre);
    B.book_return(id_book, id_person);

    // logbook
    Logs L(Day, false);
    L.Log_Return(id_person, id_book);
}

// convert book
void ManageBooks::BookList_Convert(const string & id_book, const string & id_person) {
    Book B(id_book.substr(0,8));

    B.book_convert(id_book, id_person);
}


// flash new day
void ManageBooks::BookList_DateFlash() {
    fstream f_list("book\\booklist.txt"),f_book,f_t;
    string str, line;

    getline(f_list, str);
    while (f_list.peek() != EOF) {
        getline(f_list, str);

        // flash a book
            // write in temp
        f_book.open("book\\" + str + "_books.txt", ios::in | ios::out);
        f_t.open("logbook\\temp.txt", ios::in | ios::out|ios::trunc);
        int count = 0;
        while (f_book.peek() != EOF) {
            count += 1;
            getline(f_book, line);
            if (count != 5)
                f_t << line << endl;
            else {
                count = 0;
                long num = Convert_strtolong(line);
                if (num != 100)
                    num-=1;
                f_t << Convert_longtostr(num) << endl;
            }
        }
        f_book.close();
        f_t.close();

            //rewtite in file
        f_book.open("book\\" + str + "_books.txt", ios::in | ios::out|ios::trunc);
        f_t.open("logbook\\temp.txt", ios::in | ios::out);

        while (f_t.peek() != EOF) {
            getline(f_t, line);
            f_book << line << endl;
        }

        f_book.close();
        f_t.close();
    }

    f_list.close();
}
