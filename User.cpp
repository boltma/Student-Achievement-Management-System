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

Student::Student(string&& id, string&& name) : User(std::move(id), std::move(name)) {}

void Student::AddStudent(string&& id, string&& name)
{
	string temp = id;
	if (student.count(temp))
		throw invalid_argument(temp);
	student[temp] = Student(std::move(id), std::move(name));
}
