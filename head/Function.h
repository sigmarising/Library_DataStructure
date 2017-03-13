/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Function.h
			Author:		Zhang Yun
			Version:	alpha 0.1
			Intro:		functions related to main.cpp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;

// 删除文件中的指定行
void FileLine_Delete(const string &filename, const long &line);

// 改变文件中指定行的内容
void FileLine_Change(const string &filename, const long &line, const string &things);

// 在文件的指定行之后插入内容
void FileLine_Insert(const string &filename, const long &line, const string &things);

// 返回文件指定行的内容
string FileLine_Getline(const string &filename, const long &line);