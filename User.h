#ifndef USER_H
#define USER_H

#include "Course.h"
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

extern map<string, class Teacher> teacher;
extern map<string, class Student> student;
extern map<int, vector<Student*>> class_list;

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
	float GPA = 0.0f; // ����
	int credit = 0; // ռ�������ѧ��
	int classID = -1;
	set<Course> course; // �γ�

public:
	Student() = default;
	Student(string&& id, string&& name, int classID);
	float GetGPA() const;
	int GetClass() const;
	static void AddStudent(string&& id, string&& name, int classID);
	void AddCourse(const Course& c);
	const set<Course>& GetCourse() const;
};

#endif // USER_H
