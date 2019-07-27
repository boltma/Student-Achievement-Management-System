#include "State.h"
#include "User.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

StateMachine* State::machine = nullptr; // 在machine的构造函数中被设为唯一的实例指针

MainMenu& State::MainMenu()
{
	static class MainMenu menu;
	return menu;
}

ScoreMenu& State::ScoreMenu()
{
	static class ScoreMenu menu;
	return menu;
}

ChangeMenu& State::ChangeMenu()
{
	static class ChangeMenu menu;
	return menu;
}

int State::Input(int n) // n表示可输入的最大数
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

/**
 * \brief 输入ID，若不存在ID则加入信息
 * \param text 输出提示
 * \param flag 1为教师，2为学生，3为课程
 * \return ID
 */
string State::InputID(string&& text, int flag)
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
			int a = Input(2);
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
		if (Input(2) == 1)
			break;
	}
	Teacher::AddTeacher(std::move(temp), std::move(name));
}

void State::NewStudent(const string& id)
{
	string temp = id;
	string name;
	int classID;
	while (true)
	{
		cout << "Please input student name in the next line:" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, name);
		cout << "Check student name: " << name << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		if (Input(2) == 1)
			break;
	}
	while (true)
	{
		cout << "Please input credit (no more than 20):";
		classID = Input(20); // 假设班号不超过20
		cout << "Check class number: " << classID << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		if (Input(2) == 1)
			break;
	}
	Student::AddStudent(std::move(temp), std::move(name), classID);
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
		if (Input(2) == 1)
			break;
	}
	while (true)
	{
		cout << "Please input credit (no more than 20):";
		credit = Input(20); // 假设学分不超过20
		cout << "Check credit: " << credit << endl
			<< "1.Yes" << endl
			<< "2.No" << endl;
		if (Input(2) == 1)
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
		<< "Please input your identity." << endl
		<< "1.Teacher" << endl << "2.Student" << endl << "3.Quit" << endl;
	int flag = Input(3);
	if (flag == 3)
	{
		quit = true;
		return;
	}
	machine->SetIdentity(flag == 1);
	string id = InputID("Please Input ID:", flag);
	machine->SetID(std::move(id));
}

grade ScoreMenu::InputGrade()
{
	while (true)
	{
		cout << "Please input grade:" << endl;
		string temp;
		grade g1, g2;
		cin >> temp;
		try
		{
			g1 = Course::GetGrade(std::move(temp));
		}
		catch (invalid_argument& e)
		{
			cout << "Invalid grade " << e.what() << endl;
			continue;
		}
		cout << "Please input grade again to confirm:" << endl;
		cin >> temp;
		try
		{
			g2 = Course::GetGrade(std::move(temp));
		}
		catch (invalid_argument& e)
		{
			cout << "Invalid grade " << e.what() << endl;
			continue;
		}
		if (g1 != g2)
		{
			cout << "Grades not the same." << endl;
			continue;
		}
		return g1;
	}
}

void ScoreMenu::enter()
{
	cout << "Please select from the following options." << endl
		<< "1.Inquire Grades" << endl;
	if (machine->GetIdentity())
	{
		// is_teacher = true
		cout << "2.Record Grades" << endl
			<< "3.Change Grades" << endl
			<< "4.Add Course" << endl
			<< "5.Change Course Info" << endl
			<< "6.Return to Main Menu" << endl;
		flag = Input(6);
	}
	else
	{
		cout << "2.Show GPA" << endl
			<< "3.Show Rank" << endl
			<< "4.Return to Main Menu" << endl;
		flag = Input(5);
	}
}

void ScoreMenu::exec()
{
	if (machine->GetIdentity())
	{
		switch (flag)
		{
		case 1:
			{
				// 查询成绩
				// todo: 全部成绩
				string ID = InputID("Please input ID of the course you want to inquire:", 3);
				while (true)
				{
					string studentID = InputID("Please input ID of student:", 2);
					try
					{
						grade g = course[ID].GetScore(studentID);
						cout << GradeName[g] << endl;
					}
					catch (invalid_argument& e)
					{
						cout << e.what() << endl
							<< "Please enter again." << endl;
					}
					cout << "Continue query?" << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 2)
						break;
				}
				break;
			}
		case 2:
			{
				// 录入成绩
				// todo: change course
				string ID = InputID("Please input ID of the course you want to record:", 3);
				while (true)
				{
					string studentID = InputID("Please input ID of student:", 2);
					grade g = InputGrade();
					try
					{
						course[ID].SetScore(studentID, g, false);
						student[studentID].AddCourse(course[ID]);
					}
					catch (invalid_argument& e)
					{
						cout << e.what() << endl
							<< "Please enter again." << endl;
					}
					cout << "Continue input?" << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 2)
						break;
				}
				break;
			}
		case 3:
			{
				// 更改成绩
				// todo: change course
				string ID = InputID("Please input ID of the course you want to record:", 3);
				while (true)
				{
					string studentID = InputID("Please input ID of student:", 2);
					try
					{
						grade temp = course[ID].GetScore(studentID);
						cout << "The original grade of the student is " << GradeName[temp] << endl
							<< "Are you sure to change the grade?" << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
					}
					catch (invalid_argument& e)
					{
						cout << e.what() << endl;
						continue;
					}
					if (Input(2) == 1)
					{
						grade g = InputGrade();
						course[ID].SetScore(studentID, g, true);
					}
					cout << "Continue input?" << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 2)
						break;
				}
				break;
			}
		case 4:
			{
				// 添加课程
				while (true)
				{
					cout << "Please input ID of course you want to add:";
					string ID;
					cin >> ID;
					if (course.count(ID))
					{
						cout << "Course ID already exists. Please enter again." << endl;
						continue;
					}
					cout << "Check course ID: " << ID << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 1)
						continue;
					NewCourse(ID);
					cout << "Continue input?" << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 2)
						break;
				}
				break;
			}
		case 5:
			{
				// 更改课程信息
				flag = -2;
				break;
			}
		case 6:
			{
				// 返回主页面
				flag = -1;
				break;
			}
		default:
			break;
		}
	}
	else
	{
		switch (flag)
		{
		case 1:
			{
				// 查询成绩
				cout << "1.Inquire all grades" << endl
					<< "2.Inquire grade by course id" << endl;
				if (Input(2) == 1)
				{
					for (const auto& c : student[machine->GetID()].GetCourse())
					{
						cout << setw(10) << c.GetID() << ' ' << setw(15) << c.GetName() << ' ' << c.GetScore(
							machine->GetID()) << endl;
					}
				}
				else
				{
					while (true)
					{
						cout << "Please input ID of course you want to inquire:";
						string ID;
						cin >> ID;
						try
						{
							cout << "Your grade in this course is: " << GradeName[course[ID].GetScore(machine->GetID())
							];
						}
						catch (invalid_argument& e)
						{
							cout << e.what() << endl
								<< "Please enter again." << endl;
						}
						cout << "Continue input?" << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
						if (Input(2) == 2)
							break;
					}
					break;
				}
				break;
			}
		case 2:
			{
				// 查询GPA
				cout << "Total GPA: " << student[machine->GetID()].GetGPA() << endl;
				break;
			}
		case 3:
			{
				// 显示排名
				const auto& stu = student[machine->GetID()];
				const auto& c = class_list[stu.GetClass()];
				float gpa = stu.GetGPA();
				vector<float> all_gpa, class_gpa;
				all_gpa.reserve(student.size());
				class_gpa.reserve(c.size());
				for (const auto& s : student)
				{
					all_gpa.push_back(s.second.GetGPA());
				}
				for(const auto& s: c)
				{
					class_gpa.push_back(s->GetGPA());
				}
				sort(all_gpa.begin(), all_gpa.end(), greater<>());
				sort(class_gpa.begin(), class_gpa.end(), greater<>());
				int total_rank = find(all_gpa.begin(), all_gpa.end(), gpa) - all_gpa.begin() + 1;
				int class_rank = find(class_gpa.begin(), class_gpa.end(), gpa) - class_gpa.begin() + 1;
				cout << "Total rank: " << total_rank << '/' << student.size() << endl;
				cout << "Class rank: " << class_rank << '/' << c.size() << endl;
				break;
			}
		case 4:
			{
				// 返回主菜单
				flag = -1;
				break;
			}
		default:
			break;
		}
	}
}

State* ScoreMenu::exit()
{
	if (flag == -1)
		return &MainMenu();
	if (flag == -2)
		return &ChangeMenu();
	return &State::ScoreMenu();
}

void ChangeMenu::exec()
{
	if (machine->GetIdentity())
	{
		while (true)
		{
			string ID = InputID("Please input course ID you want to change info of:", 3);
			cout << "Please select from the following options." << endl
				<< "1.Change course name" << endl
				<< "2.Change course credit" << endl;
			int flag = Input(3);
			switch (flag)
			{
			case 1:
				{
					string name;
					while (true)
					{
						cout << "Please input course name in the next line:" << endl;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						getline(cin, name);
						cout << "Check course name: " << name << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
						if (Input(2) == 1)
							break;
					}
					course[ID].SetName(name);
					break;
				}
			case 2:
				{
					int credit;
					while (true)
					{
						cout << "Please input credit (no more than 20):";
						credit = Input(20); // 假设学分不超过20
						cout << "Check credit: " << credit << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
						if (Input(2) == 1)
							break;
					}
					course[ID].SetCredit(credit);
					break;
				}
			default:
				break;
			}
		}
	}
}
