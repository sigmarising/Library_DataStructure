/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.cpp
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#include <fstream>
#include <strstream>
#include "Function.h"
using namespace std;

/* 删除文件中的指定行
 filename是带路径的完整文件名
 line是行号（从1开始计数）*/
void FileLine_Delete(const string &filename, const long &line)
{
    // copy the file without the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::trunc); // clear this temp file
    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF)
    {
        count += 1;
        getline(F_file, str);
        if (count != line)
            F_temp << str << endl;
    }

    F_temp.close();
    F_file.close();

    // rewrite in the file

    F_temp.open("logbook\\temp.txt");
    F_file.open(filename, ios::trunc); // clear file

    while (F_temp.peek() != EOF)
    {
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
void FileLine_Change(const string &filename, const long &line, const string &things)
{
    // copy the file and change the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::trunc); // clear this temp file
    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF)
    {
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

    F_temp.open("logbook\\temp.txt");
    F_file.open(filename, ios::trunc); // clear file

    while (F_temp.peek() != EOF)
    {
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
void FileLine_Insert(const string &filename, const long &line, const string &things)
{
    // copy the file and insert the only 1 line
    fstream F_temp, F_file;

    F_temp.open("logbook\\temp.txt", ios::trunc); // clear this temp file
    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF)
    {
        count += 1;
        getline(F_file, str);
        F_temp << str << endl;
        if (count == line)
            F_temp << things << endl;
    }

    F_temp.close();
    F_file.close();

    // rewrite in the file

    F_temp.open("logbook\\temp.txt");
    F_file.open(filename, ios::trunc); // clear file

    while (F_temp.peek() != EOF)
    {
        getline(F_temp, str);
        F_file << str << endl;
    }

    F_temp.close();
    F_file.close();
}

/* 返回文件指定行的内容
 filename 是带路径的完整文件名
 line 是行号 
 如果line过大则返回空串*/
string FileLine_Getline(const string &filename, const long &line)
{
    fstream F_file;

    F_file.open(filename);
    long count = 0;
    string str;

    while (F_file.peek() != EOF)
    {
        count += 1;
        getline(F_file, str);
        if (count == line)
            return str;
    }

    return string();
}

/* 将数字字符c增加1 
 如果产生进位 那么返回ture 否则返回false*/
bool Char_Addone(char &c)
{
    if ('0' < c && c < '8')
    {
        c += 1;
        return false;
    }
    else
    {
        c = '0';
        return true;
    }
}

/* 对指定的字符串增加1 并保持字符串长度不变化
 例如 str == "00000001"
 本函数执行之后得到 str == "00000002"*/
void String_Addone(string &str)
{
    int pos = str.length() - 1;
    bool carry = true;
    while (pos >= 0)
    {
        if (carry)
            if (Char_Addone(str[pos]))
                carry = true;
            else
                break;

        pos -= 1;
    }
}

// str to long
long Convert_strtolong(const string str)
{
    strstream ss;
    ss << str;
    long num;
    ss >> num;
    return num;
}

// long to str
string Convert_longtostr(const long num)
{
    strstream ss;
    ss << num;
    string str;
    ss >> str;
    return str;
}
