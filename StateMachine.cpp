#include "StateMachine.h"
#include <stdexcept>

void StateMachine::update()
{
	state->enter();
	state->exec();
	state->exit();
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

void StateMachine::exec()
{
	while (!final)
		update();
}
