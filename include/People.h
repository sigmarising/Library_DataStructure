/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+
			Name:		People.h
			Author:		Zhang Yun
			Version:	alpha 0.8
			Intro:		everything related to 
						the people 
------------------------------------------------------
				�й��˵��ļ��Ĵ������
���в������ļ�����Ϊ�ؼ�����ģ���ʱ�������ж��������ڴ�

����ͬһ����һϵ���ļ��ķ�ʽ���й����ļ�����־��

�����˴����People�ļ���֮�£�һ���˵ļ�Ҫ��Ϣ�洢һ���ļ�
(����ļ����и��˵�����ID)��ÿ���˽�������Ϣ������һ���ļ�
(����ļ���ÿ���������ID)������ԤԼ�����һ���ļ���������
�ļ�������ͬһ�˵��ļ���־ϵͳ

�����ļ�peoplelist������������е������˵�ID ��Ȩ����Ϣ
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+*/

#pragma once

#include <string>
using namespace std;


// ����: Person
// ˵��: ���а���һ���˵���Ϣ�ϲ���
class Person {
public:
	Person();						// Ĭ�Ϲ��캯��
	Person(const Person &p1);		// �������캯��
	Person(const string &filename);	// ���ļ������ж�ȡ
	Person(const string &name, const string &ID, const string &Key, const string &school, const int &limit); // �������캯�� ���ǽ������˵ĺ��� Ҫ����ļ����д���
	~Person();						// Ĭ����������

	void person_print();							// ���ڽ����͸�����Ϣ ���� ���˲��� ԤԼ��״ �ѽ�ͼ��
	void person_open(const string &filename); //����ʵʱ��������
	//void person_findbook();							// ���ڲ���ͼ�� ����ͼ����Ը���ID ���� ���� ������ ��� ������
	//void person_borrow(const string &ID_pre_book);	// ����ͼ���IDǰ׺��ɽ������ �޸�������ļ���־
	//void person_return(const string &ID_book);		// ����ͼ�������ID��ɻ������ �޸�������ļ���־
	//void person_convert();							// ��ԤԼ����ת�����ѽ���� �޸�������ļ���־
	void person_changekey(const string &Newkey);	// ��������


	string	get_personname();		// ��ȡ��������
	string	get_personID();			// ��ȡ����ID
	string	get_personschool();		// ��ȡ����ѧԺ
	string	get_personkey();		// ��ȡ��������
	int		get_personlimit();		// ��ȡ����Ȩ��


	bool Person_Notic;		// �Ƿ���֪ͨ
	long Person_honesty;	// ���Ŷ� Ĭ��100
	double Person_Debt;		// Ƿ�� Ĭ��0.0
	long Num_Borrowed;		// �ѽ�������
	long Num_Subscribe;		// ��ԤԼ����
private:
	string Person_ID;		// ����ID
	string Person_Key;		// ���˵�¼����
	string Person_Name;		// ��������
	string Person_School;	// ����ѧԺ

	int Person_Limit;		// ����Ȩ�� 0ѧ�� 1��ʦ
};


// ����: ManagePeople
// ˵��: ��������ڶ��˽��й���

class ManagePeople {
public:
	ManagePeople();							// Ĭ�Ϲ��캯��
	ManagePeople(const ManagePeople &M1);	// �������캯��
	ManagePeople(const string &filename);	// ���ļ�����ȡ����ʼ����Ϣ
	~ManagePeople();						// Ĭ����������

	bool JudgeID(const string &ID); // ��������ID���м�� ���ID�Ƿ����Ҫ�� ��12λ δ�ظ���
	bool JudgeKey(const string &ID, const string&Key); // ��½���麯��
	bool Judgesubcid(const string &bookID,const string &peopleID);		//�������Ƿ����Ȿ�����ת����

	void PeopleList_Add(const string &name, const string &ID, const string &Key, const string &school, const int &limit); // �½��� Ҫ�������ID�����ǿ��еģ�����ǰ����judgeid������ 
	void PeopleList_Pay(const string &ID); // ����Ƿ��
	void PeopleList_ChangeKey(const string &ID, const string &newkey);// ��������



	// ���黹��ת���Ĳ���ͨ��ManageBook��ʵ�� ��ManageBookʵ�ֶ�����˵��ļ���־�Ĺ�ͬ����


	void PeopleList_Find();  // �������ڲ��� ����״̬�Զ��� ��ɶԸ�����Ŀ����������


	void PeopleList_DateFlash();	// ÿ�µ�һ�� ˢ�������˵Ľ�����Ϣ
	void PeopleList_Print();		// ��ӡ��������Ϣ

	long Num_Sum_Of_People;
private:

};
