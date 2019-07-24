#include "Course.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

grade Course::GetGrade(string&& s)
{
	for_each(s.begin(), s.end(), [](char& c) { c = toupper(static_cast<unsigned char>(c)); });
	if (s == "A+")
		return _A_plus;
	if (s == "A")
		return _A;
	if (s == "A-")
		return _A_minus;
	if (s == "B+")
		return _B_plus;
	if (s == "B")
		return _B;
	if (s == "B-")
		return _B_minus;
	if (s == "C+")
		return _C_plus;
	if (s == "C")
		return _C;
	if (s == "C-")
		return _C_minus;
	if (s == "D+")
		return _D_plus;
	if (s == "D")
		return _D;
	if (s == "F")
		return _F;
	if (s == "P")
		return _P;
	if (s == "W")
		return _W;
	if (s == "I")
		return _I;
	if (s == "EX")
		return _EX;
	throw invalid_argument(s);
}

Course::Course(string&& id, string&& name, int credit) : name(name), id(id), credit(credit)
{
}

void Course::AddCourse(string&& id, string&& name, int credit)
{
	string temp = id;
	if (course.count(temp))
		throw invalid_argument(temp);
	course[temp] = Course(std::move(id), std::move(name), credit);
}

const string& Course::GetName() const
{
	return name;
}

const string& Course::GetID() const
{
	return id;
}

int Course::GetCredit() const
{
	return credit;
}

void Course::SetName(const string& s)
{
	name = s;
}

void Course::SetID(const string& s)
{
	id = s;
}

void Course::SetCredit(int c)
{
	credit = c;
}

/**
 * \brief 登入学生成绩
 * \param id 学生ID
 * \param g 学生成绩
 * \param flag 强制写入
 */
void Course::SetScore(const string& id, grade g, bool flag)
{
	if (grades.count(id) && !flag)
	{
		// 已有成绩
		throw invalid_argument("Grade already exists!");
	}
	grades[id] = g;
}

grade Course::GetScore(const string& id)
{
	if (!grades.count(id))
		throw invalid_argument("ID not found!");
	return grades[id];
}

const float GP[] = {4.0f, 4.0f, 3.7f, 3.3f, 3.0f, 2.7f, 2.3f, 2.0f, 1.7f, 1.3f, 1.0f, 0.0f, NAN, NAN, NAN, NAN};
const char* const GradeName[] = {
	"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F", "P", "W", "I", "EX"
};
