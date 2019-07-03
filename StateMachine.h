#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include <map>
#include <string>
using namespace std;

// 有限状态自动机
class StateMachine
{
private:
	class State* state;
	bool final = false; // 终止状态
	int flag = 0; // 辅助自动机状态的flag
	string id; // 当前使用者id
	void update();

public:
	StateMachine();
	void SetState(State*);
	void exec();
};

#endif // STATE_MACHINE_H
