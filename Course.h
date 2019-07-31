#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

extern map<string, class Course>& course;

// �ȼ������»��߷�ֹ����
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
 * \brief �γ���Ϣ
 */
class Course
{
private:
	string name; // ����
	string id; // �κ�
	int credit = 0; // ѧ��
	map<string, grade> grades; // ѧ���ɼ�

public:
	static grade GetGrade(string&& s); // �ַ���ת�ȼ�
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

extern const float GP[]; // �ȼ��ƶ�Ӧ�ļ���
extern const char* const GradeName[]; // �ȼ����ַ���

#endif // COURSE_H
