# 北京邮电大学 数据结构课程设计 图书馆项目

本项目文件说明

* Library_App - 此文件夹包含可执行文件exe 已测试在 Win10 14393 通过
* Library_CMD - 此文件夹包含命令行版本工程 可在 VS2017 调试
* Library_GUI - 此文件夹包含图形化版本工程 可在 Qt Creator + MSVS2015 + WinDBuger 调试
* Intro - 此文件夹下有说明文件
  * Intro_CMD - 命令行版本的交互说明
  * Intro_Files - 各个日志文件的设计说明
  * Intro_GUI - 图形化版本交互说明
  * Intro_ID - 人和图书的ID规则
* LICENCE.md - 权限说明文件
* README.md - 本文件

## 题目

### 题目描述

学校图书馆有很多图书，每个教师、学生有多种不同的借书权限和借书数量，建立图书馆管理系统，包括图书的购入、编码、借出、还回、统计、查询等功能。

## 功能要求 & 实现情况

### 功能要求

1. 每种图书包括图书编号、书名、作者、出版社、简介、购入时间、数量等信息
2. 图书馆在购书时可根据图书的信息自动生成编码
3. 教师、学生包括姓名、工作证（学生证）号、所在学院、借书权限、借书数量等信息
4. 借书时填写借书单，还书时填写借书单还书项，并记录入日志文件，借书超期要罚款
5. 基本功能有：建立图书基本信息文件、读者基本信息文件、图书入库（编码）、借书（预约）、还书、查询等
6. 查询、统计功能有：
    * 读者可根据图书的名称、编码、作者、出版社等信息查询图书的其他信息；也可根据图书的分类等信息查询图书的具体信息等，包括某图书库中尚存多少本
    * 查询教师、学生已借出的图书情况，读者的借书诚信情况（是否有过超期的情况）等
    * 图书的借阅率等
7. 对于库中已借完的图书，读者可预约，待库中有还回时能提示通知该读者
8. 模拟系统以时间为轴向前推移，每10秒左右向前推进 一天（有键盘或鼠标操作时不计时）
9. 建立日志文件，对图书借阅情况进行记录
10. 不得使用数据库

### 实现情况

所有功能均实现

增加功能：更换主题 手动计时

## 程序设计

### 开发环境

命令行版本使用 Visual Studio 2017 C++ 进行开发

图形化版本使用 Qt5.8 + MSVS2015 + WinDbuger , IDE Qt creator

### 思路简介

本程序的cmd和gui版本遵循一个思想，所有的书本信息和人的信息均不全部读入内存，不使用向量、链表在内存操作。**所有的功能基于对文件内容的改写，本程序不会因内存的大小而受到限制**。

相比之下，我们认为使用向量或者链表将所有的信息(或者可无限扩展的信息，例如一个人借的所有书)读入内存，程序的信息容量将受到机器的限制，这严重不符合现实情况。这样做是一种十分投机取巧的行为，我们认为这样的做法应该得到很低的分数。

### 命令行简介

版本为 v0.91 alpha，在tag中可以切换到

cmd版本使用标准输入输出，内部使用有限状态自动机实现用户交互，具体实现比较简单。所有日志内容很完善。

cmd版本未实现自动化时间推进处理

### 图形化简介

版本为 v1.0 beta， master分支

gui版本使用qt进行开发。使用了qt线程来完成自动化时间推进。我们在UI上定义了三种主题供用户选择。

在各个界面的输入输出我们都做了纠错处理，程序健壮性很好，提示内容恰到好处。

### 总结

本次的程序设计最重要的核心思想就是文件操作，让程序摆脱对内存的依赖。实现难点也是文件操作。