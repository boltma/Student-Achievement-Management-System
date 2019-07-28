#include "StateMachine.h"
#include "User.h"
#include <fstream>

void StateMachine::update()
{
	state->enter();
	state->exec();
	this->SetState(state->exit());
}

StateMachine::StateMachine()
{
	State::machine = this;
	state = &State::MainMenu();
	ifstream in("data.txt");
	if (!in)
		return;
	int cnt;
	string s;
	in >> s >> cnt;
	while (cnt--)
	{
		Course temp;
		in >> temp;
		string id = temp.GetID();
		course[id] = std::move(temp);
	}
	in >> s >> cnt;
	while (cnt--)
	{
		Teacher temp;
		in >> temp;
		string id = temp.GetID();
		teacher[id] = std::move(temp);
	}
	in >> s >> cnt;
	while (cnt--)
	{
		Student temp;
		in >> temp;
		string id = temp.GetID();
		student[id] = std::move(temp);
	}
	in >> s >> s >> cnt;
	while (cnt--)
	{
		int num, cnt2;
		in >> num >> cnt2;
		class_list[num] = vector<const Student*>{};
		while (cnt2--)
		{
			string id;
			in >> id;
			class_list[num].push_back(&student[id]);
		}
	}
}

StateMachine::~StateMachine()
{
	ofstream out;
	try
	{
		out.open("data.txt", ios_base::trunc);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return;
	}
	out << "Course " << course.size() << endl;
	for (const auto& c : course)
		out << c.second;
	out << "Teacher " << teacher.size() << endl;
	for (const auto& t : teacher)
		out << t.second;
	out << "Student " << student.size() << endl;
	for (const auto& s : student)
		out << s.second;
	out << "Class list " << class_list.size() << endl;
	for (const auto& c : class_list)
	{
		out << c.first << ' ' << c.second.size() << endl;
		for (const auto& s : c.second)
			out << s->GetID() << endl;
	}
	try
	{
		out.close();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

void StateMachine::SetState(State* s)
{
	state = s;
}

void StateMachine::SetIdentity(bool flag)
{
	is_teacher = flag;
}

// ÀÏÊ¦Îªtrue
bool StateMachine::GetIdentity() const
{
	return is_teacher;
}

const string& StateMachine::GetID() const
{
	return id;
}

void StateMachine::SetID(string&& id)
{
	this->id = id;
}

void StateMachine::exec()
{
	while (state != nullptr)
		update();
}
