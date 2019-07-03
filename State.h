#ifndef STATE_H
#define STATE_H

#include "Course.h"
#include "User.h"
#include <map>
#include <string>
using namespace std;

/**
 * \brief 控制台状态 \n
 * 是有限状态自动机的状态
 */
class State
{
private:
	static class StateMachine* machine;

protected:
	int input(int);	 // 读取
	string inputID(string&&, int);
	void NewTeacher(const string&);
	void NewStudent(const string&);
	void NewCourse(const string&);

public:
	static class MainMenu& MainMenu();
	virtual ~State() = default;
	virtual void enter() = 0;	 // 进入状态
	virtual void exec() = 0;	 // 执行状态
	virtual State* exit() = 0;

	friend StateMachine;
};

class MainMenu : public State
{
public:
	MainMenu() = default;
	~MainMenu() override = default;
	void enter() override;
	void exec() override {}
	State* exit() override { return this; }
};

#endif // STATE_H
