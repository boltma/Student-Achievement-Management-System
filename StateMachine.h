#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include <string>
using namespace std;

// 有限状态自动机，若state成为nullptr终止
class StateMachine
{
private:
	class State* state;
	bool is_teacher = false; // 若为student则false
	int flag = 0; // 辅助自动机状态的flag
	string id; // 当前使用者id
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
