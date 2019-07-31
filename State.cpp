#include "State.h"
#include "StateMachine.h"
#include "User.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

StateMachine* State::machine = nullptr; // 在machine的构造函数中被设为唯一的实例指针
MainMenu State::main_menu = MainMenu();
ScoreMenu State::score_menu = ScoreMenu();
ChangeMenu State::change_menu = ChangeMenu();

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
		cout << "Input # to terminate input." << endl
			<< text;
		string id;
		try
		{
			cin >> id;
			if (id == "#")
				break;
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
				throw 1;
			case 2:
				if (student.count(id))
					break;
				throw 2;
			case 3:
				if (course.count(id))
					break;
				throw 3;
			default:
				break;
			}
			return id;
		}
		catch (invalid_argument& e)
		{
			cout << e.what() << endl;
			cout << "Please enter again." << endl;
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
			return id;
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
		cout << "Please input class number (no more than 20):";
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
	while (true)
	{
		cout << "******************************************************" << endl
			<< "*  Welcome to Student Achievement Management System  *" << endl
			<< "******************************************************" << endl
			<< endl
			<< "Warning: Please do not hard exit the program or all data might be lost!" << endl
			<< endl
			<< "Please input your identity." << endl
			<< "1.Teacher" << endl << "2.Student" << endl
			<< "3.Add new identity" << endl
			<< "4.Quit" << endl;
		flag = Input(4);
		if (flag == 4 || flag == 3)
		{
			return;
		}
		machine->SetIdentity(flag == 1);
		string id = InputID("Please Input ID:", flag);
		if (id.empty())
			continue;
		machine->SetID(std::move(id));
		break;
	}
}

void MainMenu::exec()
{
	if (flag == 3)
	{
		while (true)
		{
			cout << "1.Add Teacher" << endl
				<< "2.Add Student" << endl
				<< "3.Quit" << endl;
			int a = Input(3);
			if (a == 3)
				break;
			cout << "Input # to terminate input." << endl
				<< "Please input ID of person you want to add:";
			string id;
			cin >> id;
			if (id == "#")
				continue;
			try
			{
				for (auto c : id)
				{
					if (!isalnum(c))
						throw invalid_argument(
							"Invalid character in ID! ID should only contain alphabets and numbers.");
					// ID中不出现非数字，字母
				}
			}
			catch (invalid_argument& e)
			{
				cout << e.what() << endl;
				continue;
			}
			if (a == 1 && teacher.count(id) || a == 2 && student.count(id))
			{
				cout << "Person ID already exists. Please enter again." << endl;
				continue;
			}
			cout << "Check ID: " << id << endl
				<< "1.Yes" << endl
				<< "2.No" << endl;
			if (Input(2) == 2)
				continue;
			if (a == 1)
				NewTeacher(id);
			else
				NewStudent(id);
		}
	}
}

State* MainMenu::exit()
{
	if (flag == 4)
		return nullptr;
	if (flag == 3)
		return &main_menu;
	return &score_menu;
}

grade ScoreMenu::InputGrade() const
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
			<< "6.List all courses" << endl
			<< "7.List all students" << endl
			<< "8.Get student rank" << endl
			<< "9.Return to Main Menu" << endl;
		flag = Input(9);
	}
	else
	{
		cout << "2.Show GPA" << endl
			<< "3.Show Rank" << endl
			<< "4.List all courses" << endl
			<< "5.Return to Main Menu" << endl;
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
				string id = InputID("Please input ID of the course you want to inquire:", 3);
				if (id.empty())
					break;
				while (true)
				{
					string studentID = InputID("Please input ID of student:", 2);
					if (studentID.empty())
						break;
					try
					{
						grade g = course[id].GetScore(studentID);
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
				while (true)
				{
					string id = InputID("Please input ID of the course you want to record:", 3);
					if (id.empty())
						break;
					while (true)
					{
						string studentID = InputID("Please input ID of student:", 2);
						if (studentID.empty())
							break;
						grade g = InputGrade();
						try
						{
							course[id].SetScore(studentID, g, false);
							student[studentID].AddCourse(course[id]);
						}
						catch (invalid_argument& e)
						{
							cout << e.what() << endl
								<< "Please enter again." << endl;
						}
						cout << "Continue input in this course?" << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
						if (Input(2) == 2)
							break;
					}
					cout << "Continue input in another course?" << endl
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
				while (true)
				{
					string id = InputID("Please input ID of the course you want to record:", 3);
					if (id.empty())
						break;
					while (true)
					{
						string studentID = InputID("Please input ID of student:", 2);
						if (studentID.empty())
							break;
						try
						{
							grade temp = course[id].GetScore(studentID);
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
							grade g_old = course[id].GetScore(studentID);
							course[id].SetScore(studentID, g, true);
							student[studentID].ChangeGrade(course[id], g_old);
						}
						cout << "Continue input in this course?" << endl
							<< "1.Yes" << endl
							<< "2.No" << endl;
						if (Input(2) == 2)
							break;
					}
					cout << "Continue input in another course?" << endl
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
					cout << "Input # to terminate input." << endl
						<< "Please input ID of course you want to add:";
					string id;
					cin >> id;
					if (id == "#")
						break;
					try
					{
						for (auto c : id)
						{
							if (!isalnum(c))
								throw invalid_argument(
									"Invalid character in ID! ID should only contain alphabets and numbers.");
							// ID中不出现非数字，字母
						}
					}
					catch (invalid_argument& e)
					{
						cout << e.what() << endl;
						continue;
					}
					if (course.count(id))
					{
						cout << "Course ID already exists. Please enter again." << endl;
						continue;
					}
					cout << "Check course ID: " << id << endl
						<< "1.Yes" << endl
						<< "2.No" << endl;
					if (Input(2) == 2)
						continue;
					NewCourse(id);
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
				// 列出课程
				for (const auto& c : course)
				{
					const auto& d = c.second;
					cout << setiosflags(ios_base::left) << setw(10) << d.GetID() << ' ' << setw(15) << d.GetName()
						<< ' ' << d.GetCredit() << endl;
				}
				break;
			}
		case 7:
			{
				// 列出学生
				int num;
				while (true)
				{
					cout << "Input -1 to terminate." << endl
						<< "Input 0 to list all students or input class number:";
					cin >> num;
					if (num == 0 || num == -1)
						break;
					if (!class_list.count(num))
					{
						cout << "Not invalid class number, please enter again." << endl;
						OutputClassList();
						continue;
					}
					break;
				}
				if (num == -1)
					break;
				if (num == 0)
				{
					for (const auto& s : student)
					{
						const auto& d = s.second;
						cout << setiosflags(ios_base::left) << setw(10) << d.GetID() << ' ' << setw(15) << d.GetName()
							<< ' ' << fixed << showpoint << setprecision(2) << d.GetGPA() << endl;
					}
				}
				else
				{
					for (const auto& s : class_list[num])
					{
						cout << setiosflags(ios_base::left) << setw(10) << s->GetID() << ' ' << setw(15) << s->GetName()
							<< ' ' << fixed << showpoint << setprecision(2) << s->GetGPA() << endl;
					}
				}
				break;
			}
		case 8:
			{
				// 学生排名
				int num;
				while (true)
				{
					cout << "Input -1 to terminate." << endl
						<< "Input 0 to list all students or input class number:";
					cin >> num;
					if (num == 0 || num == -1)
						break;
					if (!class_list.count(num))
					{
						cout << "Not invalid class number, please enter again." << endl;
						OutputClassList();
						continue;
					}
					break;
				}
				if (num == -1)
					break;
				vector<pair<string, Student>> v;
				if (num == 0)
				{
					v.insert(v.begin(), student.begin(), student.end());
				}
				else
				{
					for (auto& s : class_list[num])
					{
						v.emplace_back(s->GetID(), *s);
					}
				}
				sort(v.begin(), v.end(), CmpGPA);
				float curGPA = 5;
				unsigned cnt = 1;
				for (unsigned i = 1; i <= v.size(); ++i)
				{
					const auto& s = v[i - 1];
					if (s.second.GetGPA() < curGPA)
					{
						cnt = i;
						curGPA = s.second.GetGPA();
					}
					cout << cnt << "  " << setiosflags(ios_base::left) << setw(10) << s.first << ' ' << setw(15)
						<< s.second.GetName() << ' ' << fixed << showpoint << setprecision(2) << curGPA << endl;
				}
				break;
			}
		case 9:
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
						cout << setiosflags(ios_base::left) << setw(10) << c->GetID() << ' ' << setw(15) << c->GetName()
							<< ' ' << c->GetCredit() << ' ' << c->GetScore(machine->GetID()) << endl;
					}
				}
				else
				{
					while (true)
					{
						cout << "Input # to terminate input." << endl
							<< "Please input ID of course you want to inquire:";
						string id;
						cin >> id;
						if (id == "#")
							break;
						try
						{
							cout << "Your grade in this course is: " << GradeName[course[id].GetScore(machine->GetID())]
								<< endl;
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
				cout << "Total GPA: " << fixed << showpoint << setprecision(2) << student[machine->GetID()].GetGPA() <<
					endl;
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
				for (const auto& s : c)
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
				// 列出课程
				cout << "Please select from the following options." << endl
					<< "1.List courses engaged in" << endl
					<< "2.List all courses" << endl;
				const auto& stu = student[machine->GetID()];
				if (Input(2) == 1)
				{
					for (const auto& c : stu.GetCourse())
					{
						cout << setiosflags(ios_base::left) << setw(10) << c->GetID() << ' ' << setw(15) << c->GetName()
							<< ' ' << c->GetCredit() << endl;
					}
				}
				else
				{
					for (const auto& c : course)
					{
						const auto& d = c.second;
						cout << setiosflags(ios_base::left) << setw(10) << d.GetID() << ' ' << setw(15) << d.GetName()
							<< ' ' << d.GetCredit() << endl;
					}
				}
				break;
			}
		case 5:
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
		return &main_menu;
	if (flag == -2)
		return &change_menu;
	return &score_menu;
}

void ChangeMenu::exec()
{
	if (machine->GetIdentity())
	{
		while (true)
		{
			string id = InputID("Please input course ID you want to change info of:", 3);
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
					course[id].SetName(name);
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
					course[id].SetCredit(credit);
					break;
				}
			default:
				break;
			}
		}
	}
}
