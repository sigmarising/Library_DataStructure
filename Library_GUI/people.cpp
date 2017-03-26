#include <iostream>
#include <fstream>
#include "global_define.h"
#include "function.h"
#include "logbook.h"
#include "people.h"
using namespace std;


//---------------------------------------------------------------------------------
// class Person

// 默认构造函数
Person::Person() {
    Person_Notic = false;
    Person_honesty = 100;
    Person_Debt = 0.0;
    Num_Borrowed = 0;
    Num_Subscribe = 0;
}

// 拷贝构造函数
Person::Person(const Person & p1) {
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
Person::Person(const string & filename) {
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
Person::Person(const string & name, const string & ID, const string &Key, const string & school, const int & limit) {
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
    fstream f1("people\\" + ID + ".txt", fstream::out),
        f2("people\\" + ID + "_books.txt", fstream::out),
        f3("people\\" + ID + "_subc.txt", fstream::out);

    f1 << Person_ID << endl;
    f1 << Person_Key << endl;
    f1 << Person_Name << endl;
    f1 << Person_School << endl;
    f1 << Person_Limit << endl;
    f1 << Person_honesty << endl;
    f1 << Person_Debt << endl;
    f1 << Num_Borrowed << endl;
    f1 << Num_Subscribe << endl;

    f1.close();
    f2.close();
    f3.close();

}

Person::~Person() {
}


//用于实时更新数据
void Person::person_open(const string & filename) {
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

// 更改密码
void Person::person_changekey(const string & Newkey) {
    FileLine_Change("people\\" + Person_ID + ".txt", 2, Newkey);
}

string Person::get_personname() {
    return Person_Name;
}

string Person::get_personID() {
    return Person_ID;
}

string Person::get_personschool() {
    return Person_School;
}

string Person::get_personkey() {
    return Person_Key;
}

int Person::get_personlimit() {
    return Person_Limit;
}


//-------------------------------------------------------------------------
// Class ManagePeople

ManagePeople::ManagePeople() {
    Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\peoplelist.txt", 1));
}

ManagePeople::ManagePeople(const ManagePeople & M1) {
    Num_Sum_Of_People = M1.Num_Sum_Of_People;
}

ManagePeople::ManagePeople(const string & filename) {
    Num_Sum_Of_People = Convert_strtolong(FileLine_Getline("book\\"+filename+".txt", 1));
}

ManagePeople::~ManagePeople() {
}

// 本函数对ID进行检测 检测ID是否符合要求 （12位 未重复）
bool ManagePeople::JudgeID(const string & ID) {
    // we judge the length first
    if (12 != ID.length())
        return false;
    if (ID[0] != '0' && ID[0] != '1')
        return false;

    // we judge whethe the id has been used
    fstream f("people\\peoplelist.txt");

    string str;
    while (f.peek() != EOF) {
        getline(f, str);
        if (str == ID) {
            f.close();
            return false;
        }
    }

    f.close();
    return true;
}

// 登陆检验函数
// 此函数检查ID是否是存在的 并检查key是否正确
bool ManagePeople::JudgeKey(const string & ID, const string & Key) {
    fstream f("people\\peoplelist.txt");

    string str;
    getline(f, str);
    while (f.peek() != EOF) {
        getline(f, str);
        if (ID == str) {
            Person P(str);
            if (Key == P.get_personkey()) {
                f.close();
                return true;
            }
            else {
                f.close();
                return false;
            }
        }
    }

    f.close();

    return false;
}

//检验人是否有这本书可以转借阅
bool ManagePeople::Judgesubcid(const string & bookID, const string & peopleID) {
    if (bookID.length() != 12)
        return false;

    fstream f("people\\" + peopleID + "_subc.txt");

    string str;
    while (f.peek() != EOF) {
        getline(f, str);
        if (str.length() == 12 && str == bookID) {
            f.close();
            return true;
        }
    }

    f.close();
    return false;
}

// 新建人 要求给定的ID必须是可行的（可先前利用judgeid函数）
void ManagePeople::PeopleList_Add(const string & name, const string & ID, const string &Key, const string & school, const int & limit) {
    Person P(name, ID, Key, school, limit);

    // logbook
    Logs L(Day, false);
    L.Log_Addperson(ID);
}

// 还清欠款
void ManagePeople::PeopleList_Pay(const string & ID) {
    FileLine_Change("people\\" + ID + ".txt", 7, "0.0");
}

// 更改密码
void ManagePeople::PeopleList_ChangeKey(const string & ID, const string & newkey) {
    Person P(ID);
    P.person_changekey(newkey);
}


// 每新的一天 刷新所有人的借阅信息
void ManagePeople::PeopleList_DateFlash() {
    fstream f("people\\peoplelist.txt");

    string str,t;
    getline(f, str);

    while (f.peek() != EOF) {
        // get the id
        getline(f, str);

        // change the number
        fstream f_people("people\\" + str + "_books.txt", ios::in | ios::out), f_t("logbook\\temp.txt", ios::in | ios::out|ios::trunc);

        while (f_people.peek() != EOF) {
            getline(f_people, t);
            f_t << t << endl;

            getline(f_people, t);
            long num = -1 + Convert_strtolong(t);
            f_t << Convert_longtostr(num) << endl;
        }

        f_people.close(); f_t.close();

        // rewrite the file
        f_people.open("people\\" + str + "_books.txt", ios::in | ios::out|ios::trunc);
        f_t.open("logbook\\temp.txt", ios::in | ios::out);

        while (f_t.peek() != EOF) {
            getline(f_t, t);
            f_people << t << endl;
        }

        f_people.close(); f_t.close();
    }

    f.close();
}


