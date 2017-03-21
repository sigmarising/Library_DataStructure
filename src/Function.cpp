/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.cpp
			Author:		Zhang Yun
			Version:	alpha 0.91
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include "Function.h"
#include "Books.h"
#include "Global_define.h"
#include "Logbook.h"
#include "People.h"
using namespace std;

/* 删除文件中的指定行
 filename是带路径的完整文件名
 line是行号（从1开始计数）*/
void FileLine_Delete(const string & filename, const long & line) {
	// copy the file without the only 1 line
	fstream F_temp, F_file;
	
	F_temp.open("logbook\\temp.txt", ios::in | ios::out |ios::trunc); // clear this temp file
	F_file.open(filename,ios::in | ios::out);
	long count = 0;
	string str;

	while (F_file.peek() != EOF) {
		count += 1;
		getline(F_file, str);
		if (count != line) 
			F_temp << str << endl;
	}

	F_temp.close();
	F_file.close();

	// rewrite in the file

	F_temp.open("logbook\\temp.txt",ios::in | ios::out);
	F_file.open(filename, ios::in | ios::out  |ios::trunc); // clear file

	while (F_temp.peek() != EOF) {
		getline(F_temp, str);
		F_file << str << endl;
		
	}

	F_temp.close();
	F_file.close();
}

/* 改变文件中指定行的内容
 filename 是带路径的完整文件名
 line 是行号 
 things 是要代替第line行的内容 */
void FileLine_Change(const string & filename, const long & line, const string & things) {
	// copy the file and change the only 1 line
	fstream F_temp, F_file;

	F_temp.open("logbook\\temp.txt", ios::in|ios::out|ios::trunc); // clear this temp file
	F_file.open(filename,ios::in | ios::out  );
	long count = 0;
	string str;

	while (F_file.peek() != EOF) {
		count += 1;
		getline(F_file, str);
		if (count != line)
			F_temp << str << endl;
		else
			F_temp << things << endl;
	}

	F_temp.close();
	F_file.close();

	// rewrite in the file

	F_temp.open("logbook\\temp.txt", ios::in | ios::out);
	F_file.open(filename, ios::in | ios::out|ios::trunc); // clear file

	while (F_temp.peek() != EOF) {
		getline(F_temp, str);
		F_file << str << endl;

	}

	F_temp.close();
	F_file.close();
}

/* 在文件的指定行之后插入内容
 filename 是带路径的完整文件名
 line 是行号 
 things 是要插入到第line行之后的内容 */
// 0 add to the first line
void FileLine_Insert(const string & filename, const long & line, const string & things) {
	// copy the file and insert the only 1 line
	fstream F_temp, F_file;

	F_temp.open("logbook\\temp.txt", ios::in | ios::out|ios::trunc); // clear this temp file
	F_file.open(filename, ios::in | ios::out);
	long count = 0;
	if (count == line)
		F_temp << things << endl;
	string str;

	while (F_file.peek() != EOF) {
		count += 1;
		getline(F_file, str);
		F_temp << str << endl;
		if (count == line)	
			F_temp << things << endl;
	}

	F_temp.close();
	F_file.close();

	// rewrite in the file

	F_temp.open("logbook\\temp.txt", ios::in | ios::out);
	F_file.open(filename, ios::in | ios::out|ios::trunc); // clear file

	while (F_temp.peek() != EOF) {
		getline(F_temp, str);
		F_file << str << endl;

	}

	F_temp.close();
	F_file.close();
}

// 将制定内容添加到文章末尾
// filename 是带路径的完整文件名
// things 是要插入到第line行之后的内容
void FileEnd_Add(const string & filename, const string & things) {
	// copy the file and insert the only 1 line
	fstream F_file;

	F_file.open(filename,ios::app);

	F_file << things << endl;

	F_file.close();
}

// 搜索指定内容的行号（一般用于ID）
// 如果没有搜索到 返回0
long FileLine_Getnumber(const string & filename, const string & things) {
	fstream F_file;

	F_file.open(filename);
	long count = 0;
	string str;

	while (F_file.peek() != EOF) {
		count += 1;
		getline(F_file, str);
		if (str == things) {
			F_file.close();
			return count;
		}
	}

	F_file.close();
	return 0;
}

/* 返回文件指定行的内容
 filename 是带路径的完整文件名
 line 是行号 
 如果line过大则返回空串*/
string FileLine_Getline(const string & filename, const long & line) {
	fstream F_file;

	F_file.open(filename);
	long count = 0;
	string str;

	while (F_file.peek() != EOF) {
		count += 1;
		getline(F_file, str);
		if (count == line)
			return str;
	}

	return string();
}

/* 将数字字符c增加1 
 如果产生进位 那么返回ture 否则返回false*/
//bool Char_Addone(char & c) {
//	if ('0' < c && c < '8') {
//		c += 1;
//		return false;
//	}
//	else {
//		c = '0';
//		return true;
//	}
//}

/* 对指定的字符串增加1 并保持字符串长度不变化
 例如 str == "00000001"
 本函数执行之后得到 str == "00000002"*/
//void String_Addone(string & str) {
//	int pos = str.length()-1;
//	bool carry = true;
//	while (pos >= 0) {
//		if (carry)
//			if (Char_Addone(str[pos]))
//				carry = true;
//			else
//				break;
//
//		pos -= 1;
//	}
//}

// str to long
long Convert_strtolong(const string str) {
	strstream ss;
	ss << str;
	long num;
	ss >> num;
	return num;
}

// long to str
string Convert_longtostr(const long num) {
	strstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;
}

// double to str 
string Convert_doubletostr(const double num) {
	strstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;
}

// str to double
double Convert_strtodouble(const string str) {
	strstream ss;
	ss << str;
	double num;
	ss >> num;
	return num;
}

// for the main login
void login() {
	string name, key;
	system("cls");

	// get the input
	cout << "请输入ID号码: ";
	getline(cin, name);
	cout << "请输入密码: ";
	getline(cin, key);

	ManagePeople ManageP("peoplelist");
	ManageBooks ManageB("booklist");
	Logs L(Day, false);
	if (ManageP.JudgeKey(name, key)) {// student and  teacher login success
		//logbook
		L.Log_Login(name);

		// print the info
		Person P(name);
		P.person_print();

		string userinput, bookidpre,subc,key1,key2;
		bool logout = false;
		while (!logout) {
			cout << "你想做什么？\n";
			cout << "  0:查看个人信息\n";
			cout << "  1:查书\n";
			cout << "  2:借书（或预约）\n";
			cout << "  3:一键将可用预约转为借阅\n";
			cout << "  4:还书\n";
			cout << "  5:还清欠款\n";
			cout << "  6:更改密码\n";
			cout << "  7:登出\n";
			cout << "选择: ";
			getline(cin, userinput);
			char c = userinput[0];

			if (userinput.length() == 1 && ('0' <= c && c <= '7')) {
				switch (c) {
				case '0':// info-ok
					P.person_open(name);
					P.person_print();
					break;
				case '1':// find-ok
					ManageB.BookList_Find(1 + P.get_personlimit());
					break;
				case '2':// borrow subc-ok
					cout << "输入图书的ID前缀: ";
					getline(cin, bookidpre);

					if (ManageB.JudgeIDpre(bookidpre)) {
						cout << "如果此书已借完 你是否想预约？\n  1:是\n  Other:否\n 选择: ";
						getline(cin, subc);
						if (subc == "1")
							ManageB.BookList_Borrow(bookidpre, name, true);
						else
							ManageB.BookList_Borrow(bookidpre, name, false);
					}
					else {
						cout << "ID前缀错误\n";
					}
					break;
				case '3':// convert-ok
					cout << "输入你想要预约转借阅的图书的完整ID\n input: ";
					getline(cin, bookidpre);
					if (ManageP.Judgesubcid(bookidpre, name)) {
						ManageB.BookList_Convert(bookidpre, name);
					}
					else {
						cout << "完整ID错误\n";
					}
					break;
				case '4':// return book
					// we use key1 for the book we want to return
					cout << "输入要还书的完整ID: ";
					getline(cin, key1);
					if (0 == FileLine_Getnumber("people\\" + name + "_books.txt", key1)) {
						cout << "ID错误" << endl;
					}
					else {
						ManageB.BookList_Return(key1, name);
					}


					break;
				case '5':// payback-ok
					ManageP.PeopleList_Pay(name);
					break;
				case '6'://change key-ok
					cout << "键入新密码: ";
					getline(cin, key1);
					cout << "再输入一次: ";
					getline(cin, key2);
					while (key1 != key2) {
						cout << "两次输入不一致！重新输入！" << endl;
						cout << "键入新密码: ";
						getline(cin, key1);
						cout << "再输入一次: ";
						getline(cin, key2);
					}
					ManageP.PeopleList_ChangeKey(name, key1);

					break;
				case '7':// logout-ok
					logout = true;

					//logbook
					L.Log_Logout(name);
					break;
				}
			}
			else {
				cout << "输入错误\n";
			}
		}
	}
	else if ("Admin"==name && key == FileLine_Getline("logbook\\sys.txt",2)) {// the admin login succeed
		bool logout = false;
		//logbook
		L.Log_Login("Admin");

		while (!logout) {
			cout << "你想做什么？\n";
			cout << "  1:新建图书\n";
			cout << "  2:新建用户\n";
			cout << "  3:查书\n";
			cout << "  4:查人\n";
			cout << "  5:登出\n";
			cout << "选择: ";
			string userinput, bookname, bookauthor, bookpublishor, booktype;
			string peopleid, peoplekey, peoplename, peopleschool;
			int booklimit, peoplelimit;
			getline(cin, userinput);
			char c = userinput[0];

			if (userinput.length() == 1 && ('1' <= c && c <= '5')) {
				switch (c) {
				case '1':// new book-ok
					cout << "请输入图书信息\n";
					cout << "书名:";
					getline(cin, bookname);
					cout << "作者:";
					getline(cin, bookauthor);
					cout << "出版社:";
					getline(cin, bookpublishor);

					if (ManageB.BookList_BuyOld(bookname, bookauthor, bookpublishor)) {
						break;
					}

					cout << "类别:";
					getline(cin, booktype);
					cout << "权限（0均可借 1仅学生可借 2仅教师可借）:";
					cin >> booklimit;
					while (!(0 <= booklimit&&booklimit <= 2)) {
						cout << "输入有误！\n重新输入:";
						cin >> booklimit;
					}
					getchar();

					ManageB.BookList_BuyNew(bookname, bookauthor, bookpublishor, booktype, booklimit);

					break;
				case '2'://new user-ok
					cout << "输入用户信息\n";
					cout << "用户ID（12位 首位是0或1）:";
					getline(cin, peopleid);
					while (!ManageP.JudgeID(peopleid)) {
						cout << "ID有误！\n重新输入:";
						getline(cin, peopleid);
					}
					cout << "用户密码:";
					getline(cin, peoplekey);
					cout << "用户姓名:";
					getline(cin, peoplename);
					cout << "用户学院:";
					getline(cin, peopleschool);
					cout << "用户权限（0学生 1老师）:";
					cin >> peoplelimit;
					while (!(0 <= peoplelimit&&peoplelimit <= 1)) {
						
						cout << "输入有误！\n重新输入:";
						cin >> peoplelimit;
					}
					getchar();

					ManageP.PeopleList_Add(peoplename, peopleid, peoplekey, peopleschool, peoplelimit);

					break;
				case '3'://find book-ok

					cout << "是否查看所有书？\n  1:是\n  Other:否\n选择: ";
					getline(cin, userinput);

					if (userinput == "1") {
						ManageB.BookList_Print();
					}
					else
						ManageB.BookList_Find(3);

					break;
				case '4'://find people-ok
					cout << "是否查看所有用户？\n  1:是\n  Other:否\n选择: ";
					getline(cin, userinput);

					if (userinput == "1") {
						ManageP.PeopleList_Print();
					}
					else
						ManageP.PeopleList_Find();

					break;
				case '5'://logout
					logout = true;

					// logbook
					Logs L(Day, false);
					L.Log_Logout("Admin");

					break;
				}
			}
			else {
				cout << "错误输入！ \n";
			}
		}
	}
	else {//login failed
		system("cls");
		cout << "登录失败" << endl;
		system("pause");
	}
}

// flash all the info
void FlashDay() {
	ManagePeople ManageP("peoplelist");
	ManageBooks ManageB("booklist");

	ManageB.BookList_DateFlash();
	ManageP.PeopleList_DateFlash();
}
