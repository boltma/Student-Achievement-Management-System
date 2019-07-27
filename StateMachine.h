#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include <string>
using namespace std;

// ����״̬�Զ�������state��Ϊnullptr��ֹ
class StateMachine
{
private:
	class State* state;
	bool is_teacher = false; // ��Ϊstudent��false
	int flag = 0; // �����Զ���״̬��flag
	string id; // ��ǰʹ����id
	void update();

public:
	StateMachine();
	void SetState(State*);
	void SetIdentity(bool);
	bool GetIdentity() const;
	const string& GetID() const;
	void SetID(string&&);
	void exec();
};

#endif // STATE_MACHINE_H
