#include "Course.h"
#include "StateMachine.h"
#include "User.h"

map<string, Course> course;
map<string, Teacher> teacher;
map<string, Student> student;
map<int, vector<Student*>> class_list; // 班号对应的学生列表

int main(int argc, char* argv[])
{
	StateMachine machine;
	machine.exec();
}
