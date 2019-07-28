#ifndef USER_H
#define USER_H

#include "Course.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

extern map<string, class Teacher> teacher;
extern map<string, class Student> student;
extern map<int, vector<const Student*>> class_list;

/**
 * \brief �ɼ�����ϵͳ�û���Ϣ
 */
class User
{
	//todo: Add Password if possible

protected:
	string id; // ѧ��/����
	string name; // ����

public:
	User() = default;
	User(string&& id, string&& name);
	const string& GetID() const;
	const string& GetName() const;
};

class Teacher : public User
{
public:
	Teacher() = default;
	Teacher(string&& id, string&& name);
	friend istream& operator>> (istream&, Teacher&);
	friend ostream& operator<< (ostream&, const Teacher&) noexcept;
	static void AddTeacher(string&& id, string&& name);
};

/**
 * \brief ѧ��������Ϣ
 */
class Student : public User
{
private:
	float GPA = 0.0f; // ����
	int credit = 0; // ռ�������ѧ��
	int classID = -1;
	vector<const Course*> course_list; // �γ�

public:
	Student() = default;
	Student(string&& id, string&& name, int classID);
	friend istream& operator>> (istream&, Student&);
	friend ostream& operator<< (ostream&, const Student&) noexcept;
	float GetGPA() const;
	int GetClass() const;
	static void AddStudent(string&& id, string&& name, int classID);
	void AddCourse(const Course& c);
	const vector<const Course*>& GetCourse() const;
};

bool CmpGPA(const pair<string, Student>&, const pair<string, Student>&);

istream& operator>> (istream&, Teacher&);
istream& operator>> (istream&, Student&);
ostream& operator<< (ostream&, const Teacher&) noexcept;
ostream& operator<< (ostream&, const Student&) noexcept;

#endif // USER_H
