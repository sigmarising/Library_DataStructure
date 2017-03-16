/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		People.cpp
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		everything related to 
						the people 
------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "Global_define.h"
#include "Function.h"
#include "People.h"
using namespace std;

//---------------------------------------------------------------------------------
// class Person

// 默认构造函数
Person::Person()
{
    Person_Notic = false;
    Person_honesty = 100;
    Person_Debt = 0.0;
    Num_Borrowed = 0;
    Num_Subscribe = 0;
}

// 拷贝构造函数
Person::Person(const Person &p1)
{
    Person_Notic = p1.Person_Notic;
    Person_honesty = p1.Person_honesty;
    Person_Debt = p1.Person_Debt;
    Num_Borrowed = p1.Num_Borrowed;
    Num_Subscribe = p1.Num_Subscribe;

    Person_ID = p1.Person_ID;
    Person_Key = p1.Person_Key;
    Person_Name = p1.Person_Name;
    Person_School = p1.Person_School;
    Person_Limit = p1.Person_Limit;
}

// 从文件名进行读取
// such as Person P("000000000001");
Person::Person(const string &filename)
{
    ifstream file("people\\" + filename + ".txt");

    getline(file, Person_ID);
    getline(file, Person_Key);
    getline(file, Person_Name);
    getline(file, Person_School);
    file >> Person_Limit;
    file >> Person_honesty;
    file >> Person_Debt;
    file >> Num_Borrowed;
    file >> Num_Subscribe;

    file.close();
}

// 参数构造函数 这是建立新人的函数 要求对文件进行创建
// 调用前应该保证ID的正确性
Person::Person(const string &name, const string &ID, const string &Key, const string &school, const int &limit)
{
    Person_Notic = false;
    Person_honesty = 100;
    Person_Debt = 0.0;
    Num_Borrowed = 0;
    Num_Subscribe = 0;
    Person_Name = name;
    Person_ID = ID;
    Person_Key = Key;
    Person_School = school;
    Person_Limit = limit;

    // update the peoplelist
    long num = Convert_strtolong(FileLine_Getline("people\\peoplelist.txt", 1));
    FileLine_Change("people\\peoplelist.txt", 1, Convert_longtostr(num + 1));
    FileLine_Insert("people\\peoplelist.txt", 1, ID);

    // create three files
    fstream f1("people\\" + ID + ".txt"), f2("people\\" + ID + "_books.txt"), f3("people\\" + ID + "_subc.txt");

    f1 << Person_ID << endl;
    f1 << Person_Key << endl;
    f1 << Person_Name << endl;
    f1 << Person_School << endl;
    f1 << Person_Limit << endl;
    f1 << Person_Debt << endl;
    f1 << Num_Borrowed << endl;
    f1 << Num_Subscribe << endl;

    f1.close();
    f2.close();
    f3.close();
}

Person::~Person()
{
}

// 用于将发送个人信息 包括 个人参数 预约现状 已借图书
void Person::person_print()
{
    cout << endl;
    cout << "个人信息:\n";
    cout << "ID:" << Person_ID << endl;
    cout << "Name:" << Person_Name << endl;
    cout << "School:" << Person_School << endl;
    cout << "Limit:";
    if (Person_Limit == 0)
        cout << "学生" << endl;
    else
        cout << "老师" << endl;
    cout << "Honesty:" << Person_honesty << endl;
    cout << "Debt:" << Person_Debt << endl;

    cout << endl;
    cout << "已借图书:" << Num_Borrowed << endl;
    if (Num_Borrowed > 0)
    {
        fstream f("people\\" + Person_ID + "_book.txt");
        string str;

        while (f.peek() != EOF)
        {
            getline(f, str);
            cout << "ID:" << str << endl;
            cout << "BookName:" << FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2) << endl;

            getline(f, str);
            cout << "DueTime:" << str << endl
                 << endl;
        }

        f.close();
    }

    cout << endl;
    cout << "预约图书:" << Num_Subscribe << endl;
    if (Num_Subscribe > 0)
    {
        fstream f("people\\" + Person_ID + ".txt");
        string str;

        while (f.peek() != EOF)
        {
            getline(f, str);
            cout << "BookName: " << FileLine_Getline("book\\" + str.substr(0, 8) + ".txt", 2) << endl;

            getline(f, str);
            cout << "State: ";
            if (0 == Convert_strtolong(str))
                cout << "不可用" << endl
                     << endl;
            else
                cout << "有书" << endl
                     << endl;
        }

        f.close();
    }
}

// 更改密码
void Person::person_changekey(const string &Newkey)
{
    FileLine_Change("people\\" + Person_ID + ".txt", 2, Newkey);
}

string Person::get_personname()
{
    return Person_Name;
}

string Person::get_personID()
{
    return Person_ID;
}

string Person::get_personschool()
{
    return Person_School;
}

string Person::get_personkey()
{
    return Person_Key;
}

int Person::get_personlimit()
{
    return Person_Limit;
}

//-------------------------------------------------------------------------
// Class ManagePeople

ManagePeople::ManagePeople()
{
    Num_Sum_Of_People = 0;
}

ManagePeople::ManagePeople(const ManagePeople &M1)
{
    Num_Sum_Of_People = M1.Num_Sum_Of_People;
}

ManagePeople::ManagePeople(const string &filename)
{
    Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\peoplelist.txt", 1));
}

ManagePeople::~ManagePeople()
{
}
