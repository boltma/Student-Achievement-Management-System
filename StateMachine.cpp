#include "StateMachine.h"
#include <stdexcept>

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
	// Todo: initialize maps
}

void StateMachine::SetState(State* s)
{
	state = s;
}

void StateMachine::SetIdentity(bool flag)
{
	is_teacher = flag;
}

bool StateMachine::GetIdentity()
{
	return is_teacher;
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
