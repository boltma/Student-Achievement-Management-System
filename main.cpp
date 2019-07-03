#include "Course.h"
#include "StateMachine.h"
#include "User.h"

map<string, Course> course;
map<string, Teacher> teacher;
map<string, Student> student;

int main(int argc, char* argv[])
{
	StateMachine machine;
	machine.exec();
}
