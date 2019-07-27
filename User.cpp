#include "User.h"
#include <stdexcept>

User::User(string&& id, string&& name) : id(id), name(name) {}

Teacher::Teacher(string&& id, string&& name) : User(std::move(id), std::move(name)) {}

void Teacher::AddTeacher(string&& id, string&& name)
{
	string temp = id;
	if (teacher.count(temp))
		throw invalid_argument(temp);
	teacher[temp] = Teacher(std::move(id), std::move(name));
}

Student::Student(string&& id, string&& name, int classID) : User(std::move(id), std::move(name)), classID(classID) {}

float Student::GetGPA() const
{
	return GPA;
}

int Student::GetClass() const
{
	return classID;
}

void Student::AddStudent(string&& id, string&& name, int classID)
{
	string temp = id;
	if (student.count(temp))
		throw invalid_argument(temp);
	student[temp] = Student(std::move(id), std::move(name), classID);
	if(!class_list.count(classID))
	{
		class_list[classID] = vector<Student*>{};
	}
	class_list[classID].push_back(&student[temp]);
}

void Student::AddCourse(const Course& c)
{
	course.insert(c);
	grade g = c.GetScore(id);
	if (!isnan(GP[g]))
	{
		float total = GPA * static_cast<float>(credit) + GP[g] * static_cast<float>(c.GetCredit());
		credit += c.GetCredit();
		GPA = total / static_cast<float>(credit);
	}
}

const set<Course>& Student::GetCourse() const
{
	return course;
}
