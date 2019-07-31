#ifndef STATE_H
#define STATE_H

#include "Course.h"
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
	int flag = 0;
	int Input(int); // 读取
	string InputID(string&&, int);
	static class MainMenu main_menu;
	static class ScoreMenu score_menu;
	static class ChangeMenu change_menu;
	void NewTeacher(const string&);
	void NewStudent(const string&);
	void NewCourse(const string&);

public:
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
	void exec() override;
	State* exit() override;
};

class ScoreMenu : public State
{
public:
	grade InputGrade() const;
	void enter() override;
	void exec() override;
	State* exit() override; 
};

class ChangeMenu : public State
{
public:
	void enter() override {}
	void exec() override;
	State* exit() override { return &score_menu; }
};

#endif // STATE_H
