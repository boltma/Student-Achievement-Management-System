#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "User.h"
#include <string>
using namespace std;

class Info
{
protected:
	bool is_teacher = false; // ��Ϊstudent��false
	string id; // ��ǰʹ����id

public:
	void SetIdentity(bool);
	bool GetIdentity() const;
	const string& GetID() const;
	void SetID(string&&);
};

class Data
{
protected:
	map<string, Course> course;
	map<string, Teacher> teacher;
	map<string, Student> student;
	map<int, vector<const Student*>> class_list; // ��Ŷ�Ӧ��ѧ���б�

public:
	void ReadData();
	void WriteData();
};

// ����״̬�Զ�������state��Ϊnullptr��ֹ
class StateMachine: public Info, public Data
{
private:
	class State* state;
	void update();

public:
	StateMachine();
	~StateMachine() = default;
	void SetState(State*);
	void exec();
	map<string, Course>& GetCourse();
	map<string, Teacher>& GetTeacher();
	map<string, Student>& GetStudent();
	map<int, vector<const Student*>>& GetClassList();
};

#endif // STATE_MACHINE_H
