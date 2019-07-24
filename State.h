#ifndef STATE_H
#define STATE_H

#include "Course.h"
#include "StateMachine.h"
#include <string>
using namespace std;

/**
 * \brief 控制台状态 \n
 * 是有限状态自动机的状态
 */
class State
{
protected:
	static class StateMachine* machine;
	int Input(int); // 读取
	string InputID(string&&, int);
	void NewTeacher(const string&);
	void NewStudent(const string&);
	void NewCourse(const string&);

public:
	static class MainMenu& MainMenu();
	static class ScoreMenu& ScoreMenu();
	virtual ~State() = default;
	virtual void enter() = 0; // 进入状态
	virtual void exec() = 0; // 执行状态
	virtual State* exit() = 0;

	friend StateMachine;
};

class MainMenu : public State
{
public:
	void enter() override;

	void exec() override
	{
	}

	State* exit() override { return reinterpret_cast<State*>(&ScoreMenu()); }
};

class ScoreMenu : public State
{
private:
	int flag = 0;

public:
	grade InputGrade();
	void enter() override;
	void exec() override;
	State* exit() override { return nullptr; }
};

#endif // STATE_H
