#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

extern map<string, class Course>& course;

// 等级，加下划线防止重名
enum grade
{
	_A_plus,
	_A,
	_A_minus,
	_B_plus,
	_B,
	_B_minus,
	_C_plus,
	_C,
	_C_minus,
	_D_plus,
	_D,
	_F,
	_P,
	_W,
	_I,
	_EX
};

/**
 * \brief 课程信息
 */
class Course
{
private:
	string name; // 课名
	string id; // 课号
	int credit = 0; // 学分
	map<string, grade> grades; // 学生成绩

public:
	static grade GetGrade(string&& s); // 字符串转等级
	Course() = default;
	Course(string&& id, string&& name, int credit);
	bool operator< (const Course&) const;
	friend istream& operator>> (istream&, Course&);
	friend ostream& operator<< (ostream&, const Course&) noexcept;
	static void AddCourse(string&& id, string&& name, int credit);
	const string& GetName() const;
	const string& GetID() const;
	int GetCredit() const;
	void SetName(const string&);
	void SetID(const string&);
	void SetCredit(int);
	void SetScore(const string&, grade, bool);
	grade GetScore(const string&) const;
};

istream& operator>> (istream&, Course&);
ostream& operator<< (ostream&, const Course&) noexcept;

extern const float GP[]; // 等级制对应的绩点
extern const char* const GradeName[]; // 等级的字符串

#endif // COURSE_H
