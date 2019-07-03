#include "State.h"
#include <iostream>
#include <stdexcept>

StateMachine* State::machine = nullptr; // 在machine的构造函数中被设为唯一的实例指针

MainMenu& State::MainMenu()
{
	static class MainMenu menu;
	return menu;
}

int State::input(int n) // n表示可输入的最大数
{
	while (true)
	{
		int i;
		try
		{
			cin >> i;
			if (!cin.good() || cin.peek() != 10 && cin.peek() != 13) // 10为\n，13为\r
				throw invalid_argument("Invalid argument!");
			if (i > n || i <= 0)
				throw invalid_argument("Out of range!");
			return i;
		}
		catch (std::invalid_argument& e)
		{
			cout << e.what() << endl;
			cout << "Please input again:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

// flag = 1为老师，2为学生，3为课程
string State::inputID(string&& text, int flag)
{
	while (true)
	{
		cout << text;
		string id;
		try
		{
			cin >> id;
			for (auto c : id)
			{
				if (!isalnum(c))
					throw invalid_argument("Invalid character in ID! ID should only contain alphabets and numbers.");
				// ID中不出现非数字，字母
			}
			switch (flag)
			{
			case 1:
				if (teacher.count(id))
					break;
			case 2:
				if (student.count(id))
					break;
			case 3:
				if (course.count(id))
					break;
			default:
				throw flag;
			}
			return id;
		}
		catch (invalid_argument& e)
		{
			cout << e.what() << endl;
		}
		catch (int f)
		{
			cout << "ID:" << id << " not found!" << endl
				<< "Add ID?" << endl
				<< "1.Yes" << endl
				<< "2.No" << endl;
			int a = input(2);
			if (a == 2)
				continue;
			switch (f)
			{
			case 1:
				NewTeacher(id);
				break;
			case 2:
				NewStudent(id);
				break;
			case 3:
				NewCourse(id);
				break;
			default:
				break;
			}
			break;
		}
	}
	return "";
}

void State::NewTeacher(const string& id)
{
	string temp = id;
	string name;
	while (true)
	{
		cout << "Please input teacher name in the next line:" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, name);
		cout << "Check teacher name: " << name << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		int flag = input(2);
		if (flag == 1)
			break;
	}
	Teacher::AddTeacher(std::move(temp), std::move(name));
}

void State::NewStudent(const string& id)
{
	string temp = id;
	string name;
	while (true)
	{
		cout << "Please input student name in the next line:" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, name);
		cout << "Check student name: " << name << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		int flag = input(2);
		if (flag == 1)
			break;
	}
	Student::AddStudent(std::move(temp), std::move(name));
}

void State::NewCourse(const string& id)
{
	string temp = id;
	string name;
	int credit;
	while (true)
	{
		cout << "Please input course name in the next line:" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, name);
		cout << "Check course name: " << name << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		int flag = input(2);
		if (flag == 1)
			break;
	}
	while (true)
	{
		cout << "Please input credit (no more than 20):";
		credit = input(20); // 假设学分不超过20
		cout << "Check credit: " << credit << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		int flag = input(2);
		if (flag == 1)
			break;
	}
	Course::AddCourse(std::move(temp), std::move(name), credit);
}

void MainMenu::enter()
{
	cout << "******************************************************" << endl
		<< "*  Welcome to Student Achievement Management System  *" << endl
		<< "******************************************************" << endl
		<< endl
		<< "Please input your identity" << endl
		<< "1. Teacher" << endl << "2. Student" << endl;
	int flag = input(2);
	string id = inputID("Please Input ID:" , flag);
}
