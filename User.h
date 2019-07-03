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
 * \brief 成绩管理系统用户信息
 */
class User
{
private:
	string id;			// 学号/工号
	string name;		// 姓名

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
 * \brief 学生个人信息
 */
class Student : public User
{
private:
	float GPA = 0.0f;	// 绩点
	set<Course> course; // 课程

public:
	Student() = default;
	Student(string&& id, string&& name);
	static void AddStudent(string&& id, string&& name);
};

#endif // USER_H
