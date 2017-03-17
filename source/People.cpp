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
    Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\peoplelist.txt", 1));
}

ManagePeople::ManagePeople(const ManagePeople &M1)
{
    Num_Sum_Of_People = M1.Num_Sum_Of_People;
}

ManagePeople::ManagePeople(const string &filename)
{
    Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\" + filename + ".txt", 1));
}

ManagePeople::~ManagePeople()
{
}

// 本函数对ID进行检测 检测ID是否符合要求 （12位 未重复）
bool ManagePeople::JudgeID(const string &ID)
{
    // we judge the length first
    if (12 != ID.length())
        return false;

    // we judge whethe the id has been used
    fstream f("people\\peoplelist.txt");

    string str;
    while (f.peek() != EOF)
    {
        getline(f, str);
        if (str == ID)
        {
            f.close();
            return false;
        }
    }

    f.close();
    return true;
}

// 登陆检验函数
// 此函数检查ID是否是存在的 并检查key是否正确
bool ManagePeople::JudgeKey(const string &ID, const string &Key)
{
    fstream f("people\\peoplelist.txt");

    string str;
    getline(f, str);
    while (f.peek() != EOF)
    {
        getline(f, str);
        if (ID == str)
        {
            Person P(str);
            if (Key == P.get_personkey())
            {
                f.close();
                return true;
            }
            else
            {
                f.close();
                return false;
            }
        }
    }

    f.close();

    return false;
}

// 新建人 要求给定的ID必须是可行的（可先前利用judgeid函数）
void ManagePeople::PeopleList_Add(const string &name, const string &ID, const string &Key, const string &school, const int &limit)
{
    Person P(name, ID, Key, school, limit);
}

// 本函数内部有 有限状态自动机 完成对各个项目的搜索操作
void ManagePeople::PeopleList_Find()
{
    cout << endl;
    cout << "以下是查人选项:\n";
    cout << "  1:根据ID\n";
    cout << "  2:根据姓名\n";
    cout << "  3:根据学院\n";
    cout << "  4:根据权限\n";
    cout << "选择: ";
    string str, t;
    getline(cin, str);

    while (!(0 == str.length() && ('1' <= str[0] && str[0] <= '4')))
    {
        cout << "输入错误\n重新输入: ";
        getline(cin, str);
    }
    char c = str[0];

    cout << "\n 输入: ";
    getline(cin, str);

    fstream f("people\\peoplelist.txt");

    getline(f, t);
    switch (c)
    {
    case 1: // ID
        while (f.peek() != EOF)
        {
            getline(f, t);

            if (string::npos != t.find(str))
            {
                Person P(t);
                P.person_print();
            }
        }
        break;
    case 2: // name
        while (f.peek() != EOF)
        {
            getline(f, t);
            Person P(t);

            if (string::npos != P.get_personname().find(str))
            {
                P.person_print();
            }
        }
        break;
    case 3: // school
        while (f.peek() != EOF)
        {
            getline(f, t);
            Person P(t);

            if (string::npos != P.get_personschool().find(str))
            {
                P.person_print();
            }
        }
        break;
    case 4: // limit
        while (f.peek() != EOF)
        {
            getline(f, t);
            Person P(t);
            int i = int(Convert_strtolong(str));

            if (i == P.get_personlimit())
            {
                P.person_print();
            }
        }
        break;
    }

    f.close();
}

// 每新的一天 刷新所有人的借阅信息
void ManagePeople::PeopleList_DateFlash()
{
    fstream f("people\\peoplelist.txt");

    string str;
    getline(f, str);

    while (f.peek() != EOF)
    {
        // get the id
        getline(f, str);

        // change the number
        fstream f_people("people\\" + str + "_books.txt"), f_t("logbook\\temp.txt", ios::trunc);

        while (f_people.peek() != EOF)
        {
            getline(f_people, str);
            f_t << str << endl;

            getline(f_people, str);
            long num = -1 + Convert_strtolong(str);
            f_t << Convert_longtostr(num) << num;
        }

        f_people.close();
        f_t.close();

        // rewrite the file
        f_people.open("people\\" + str + "_books.txt", ios::trunc);
        f_t.open("logbook\\temp.txt");

        while (f_t.peek() != EOF)
        {
            getline(f_t, str);
            f_people << str << endl;
        }

        f_people.close();
        f_t.close();
    }

    f.close();
}

// 打印所有人信息
void ManagePeople::PeopleList_Print()
{
    fstream f("people\\peoplelist.txt");
    string str;

    getline(f, str);
    while (f.peek() != EOF)
    {
        getline(f, str);
        Person P(str);
        P.person_print();
    }

    f.close();
}
