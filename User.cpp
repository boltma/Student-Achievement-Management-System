#include "User.h"
#include <stdexcept>

User::User(string&& id, string&& name) : id(id), name(name) {}

const string& User::GetID() const
{
	return id;
}

const string& User::GetName() const
{
	return name;
}

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
	if (!class_list.count(classID))
	{
		class_list[classID] = vector<const Student*>{};
	}
	class_list[classID].push_back(&student[temp]);
}

void Student::AddCourse(const Course& c)
{
	course_list.push_back(&c);
	grade g = c.GetScore(id);
	if (!isnan(GP[g]))
	{
		float total = GPA * static_cast<float>(credit) + GP[g] * static_cast<float>(c.GetCredit());
		credit += c.GetCredit();
		GPA = total / static_cast<float>(credit);
	}
}

const vector<const Course*>& Student::GetCourse() const
{
	return course_list;
}

bool CmpGPA(const pair<string, Student>& a, const pair<string, Student>& b)
{
	return a.second.GetGPA() < b.second.GetGPA();
}

istream& operator>>(istream& in, Teacher& t)
{
	in >> t.id;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(in, t.name);
	return in;
}

istream& operator>>(istream& in, Student& s)
{
	in >> s.id >> s.classID >> s.credit >> s.GPA;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(in, s.name);
	while (true)
	{
		string id;
		in >> id;
		if (id == "#")
			break;
		s.course_list.push_back(&course[id]);
	}
	return in;
}

ostream& operator<<(ostream& out, const Teacher& t) noexcept
{
	out << t.id << endl
		<< t.name << endl;
	return out;
}

ostream& operator<<(ostream& out, const Student& s) noexcept
{
	out << s.id << ' ' << s.classID << ' ' << s.credit << ' ' << s.GPA << endl
		<< s.name << endl;
	for (const auto& c : s.course_list)
	{
		out << c->GetID() << endl;
	}
	out << '#' << endl;
	return out;
}

void OutputClassList()
{
	cout << "Currently available class number: ";
	if (class_list.empty())
		cout << "null" << endl;
	else
	{
		for (const auto& c : class_list)
			cout << c.first << ' ';
		cout << endl;
	}
}
