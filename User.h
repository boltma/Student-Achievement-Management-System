#ifndef USER_H
#define USER_H

#include "Course.h"
#include <map>
#include <set>
#include <string>
using namespace std;

extern map<string, class Teacher> teacher;
extern map<string, class Student> student;

/**
 * \brief �ɼ�����ϵͳ�û���Ϣ
 */
class User
{
private:
	string id;			// ѧ��/����
	string name;		// ����

public:
	User() = default;
	User(string&& id, string&& name);
};

class Teacher : public User
{
public:
	Teacher() = default;
	Teacher(string&& id, string&& name);
	static void AddTeacher(string&& id, string&& name);
};

/**
 * \brief ѧ��������Ϣ
 */
class Student : public User
{
private:
	float GPA = 0.0f;	// ����
	set<Course> course; // �γ�

public:
	Student() = default;
	Student(string&& id, string&& name);
	static void AddStudent(string&& id, string&& name);
};

#endif // USER_H
