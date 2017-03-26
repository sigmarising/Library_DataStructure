/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		Books.h
			Author:		Zhang Yun
			Version:	alpha 0.91
			Intro:		everything related to 
						the Books 
------------------------------------------------------
				�й�����ļ��Ĵ������
���в������ļ�����Ϊ�ؼ�����ģ���ʱ�������ж��������ڴ�

����ͬһ����һϵ���ļ��ķ�ʽ���й����ļ�����־��

����������book�ļ���֮�£�һ����ļ�Ҫ��Ϣ�洢һ���ļ�
(����ļ������������IDǰ׺)��ÿ�������Ϣ������һ���ļ�
(����ļ���ÿ���������ID)������ԤԼ�ߴ�һ���ļ���������
�ļ�������ͬһ����ļ��ϵ��ļ���־ϵͳ

�����ļ�booklist������������е��������IDǰ׺
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;


// ����: Item
// ˵��: ���а���һ�������Ϣ ����һ��������
struct Item {
	string ID_Book;			// �Ȿ�������ID
	string ID_Borrower;		// �Ȿ��Ľ���|ԤԼ�ߵ�ID
	string Time_InHub;		// �Ȿ������ʱ��
	int Time_Due;			// �Ȿ��Ľ���ʣ��ʱ��
	int state;				// �Ȿ���״̬
							// ״̬˵��: 0-�ɽ�� 1-�ѽ�� 2-��ԤԼ
};


// ����: Book
// ˵��: ����һ����ļ��� 
// ͨ�����ǲ���Ҫ���������������Ϣ�����ڴ�
// ���Ա����������ʵ�ֶ�һ���������ļ����в���
class Book {
public:
	Book();							// Ĭ�Ϲ��캯��
	Book(const Book &book1);		// �������캯��
	Book(const string & filename);	// �Զ��幹�캯�� �� filename.txt �ļ��г�ʼ����������Ϣ
	Book(const string & bookname, const string & bookauthor, const string & bookpublisher, const string & booktype, const int & booklimit); //����¹�����鲻�������� ��ôӦ�ô���һ���µ����͵��� ID_pre �� Number �Զ����� �����������ļ���־
	~Book();						// Ĭ����������


	bool is_equal(const string & name, const string & author, const string &publishor);	// ���� ���� ���� ������ ���ж� ����������Ƿ��뱾����ȼ�

	void book_addbook();								// ������һ���µ��� Ҫ����� <��Ա���� �����ļ� ����ļ� ԤԼ�ļ�> ԤԼ���˿��Խ���ʱ �����˵���ʾ��Ϣ
	void book_subscribe(const string & ID_borrower);	// ������һ��ԤԼ�� Ҫ����� <��Ա���� �����ļ� ����ļ� ԤԼ�ļ�>
	void book_convert(const string & ID_book, const string & ID_borrower);		// ��ԤԼת���ɽ��� Ҫ����� <��Ա���� �����ļ� ����ļ� ԤԼ�ļ�>
	void book_borrow(const string & ID_borrower);		// ������һ�������� Ҫ����� <��Ա���� �����ļ� ����ļ� ԤԼ�ļ�>
	void book_return(const string & ID_book, const string & ID_borrower);	// ���鶯����ز��� Ҫ����� <��Ա���� �����ļ� ����ļ� ԤԼ�ļ�> ԤԼ���˿��Խ���ʱ �����˵���ʾ��Ϣ
	void book_print();									// ��ӡ������Ϣ


	string get_bookname();			// �õ�����
	string get_bookauthor();		// �õ�����
	string get_bookpublisher();		// �õ�������
	string get_booktype();			// �õ����
	string get_ID_pre();			// �õ� ID ǰ׺
	int get_bookLimit();			// �õ�Ȩ��ֵ


	long Num_Borrowed;		// �ѽ������
	long Num_Subscribe;		// ��ԤԼ���� �������Ŷ����� ����ԤԼ����ʱ��һ����
	long Num_Available;		// �ɽ������
	long Num_Sum;			// ����������
private:
	string Book_Name;		// ����
	string Book_Author;		// ������
	string Book_Publisher;	// ������
	string Book_Type;		// ���
	
	string ID_pre;			// ID ǰ׺

	int Book_Limit;			// Ȩ�� 0���ɽ� 1��ѧ���ɽ� 2����ʦ�ɽ�
};


// ����: ManageBooks
// ˵��: ���������г�Ա�������Ƕ�����ͼ����й����ϵͳ ʹ��ʱ����һ��������
class ManageBooks {
public:
	ManageBooks();							// Ĭ�Ϲ��캯��
	ManageBooks(const ManageBooks & M);		// �������캯��
	ManageBooks(const string & filename);	// ��filename.txt����ɶ��������Ϣ����
	~ManageBooks();							// Ĭ����������

	bool JudgeIDpre(const string &idpre);	// �ж�idpre�Ƿ��Ǵ��ڵ�

	bool BookList_BuyOld(const string & bookname, const string & bookauthor, const string & bookpublisher); // ����ͼ�� ����������Ϣ �޸������� booklist�ļ�ҲӦ�ñ�����
	void BookList_BuyNew(const string & bookname, const string & bookauthor, const string & bookpublisher, const string & booktype, const int & booklimit); // ����ͼ�� ����������Ϣ �������ļ� booklist�ļ�ҲӦ�ñ�����
	void BookList_Borrow(const string & id_pre, const string & id_person, bool Subscribe);	// ���� ��������id��Ϣ �����Զ��ж� ���н��鶯������ԤԼ����(�� Subscribe Ϊ TRUE ʱ�Ž���ԤԼ ���򲻽���ԤԼ) ����ʱ���Զ���������id��
	void BookList_Return(const string & id_book, const string & id_person);					// ����id��Ϣ��ɻ������
	void BookList_Convert(const string & id_book, const string & id_person);			// �����˵�id��Ϣ���ԤԼת�������
	void BookList_Find(const int limit);	// �������ڲ��� ����״̬�Զ��� ��ɶԸ�����Ŀ����������
	
	void BookList_DateFlash();	// ÿ�µ�һ�� ˢ������ͼ��Ľ�����Ϣ
	void BookList_Print();		// ��ӡ��������Ϣ


	long Num_Sum_Of_Books;	// ��ʾ�ж��ٲ�ͬ�������
private:

};
