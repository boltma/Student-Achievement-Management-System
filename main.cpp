#include "StateMachine.h"
#include "User.h"

StateMachine machine;
map<string, Course>& course = machine.GetCourse();
map<string, Teacher>& teacher = machine.GetTeacher();
map<string, Student>& student = machine.GetStudent();
map<int, vector<const Student*>>& class_list = machine.GetClassList();

int main(int argc, char* argv[])
{
	machine.ReadData();
	machine.exec();
	machine.WriteData();
}
