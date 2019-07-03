#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include <map>
#include <string>
using namespace std;

// ����״̬�Զ���
class StateMachine
{
private:
	class State* state;
	bool final = false; // ��ֹ״̬
	int flag = 0; // �����Զ���״̬��flag
	string id; // ��ǰʹ����id
	void update();

public:
	StateMachine();
	void SetState(State*);
	void exec();
};

#endif // STATE_MACHINE_H
