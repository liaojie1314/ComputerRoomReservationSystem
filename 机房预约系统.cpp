#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用老师子菜单
		teacher->openMenu();
		//将父类指针转为子类指针
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		//接收用户选项
		cin >> select;
		if (select == 1)//查看所有预约
		{
			tea->showAllOrder();
		}
		else if (select == 2)//审核预约
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;//销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入学生子菜单界面
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单
		student->openMenu();
		//将父类指针转为子类指针
		Student* stu = (Student*)student;
		int select = 0;
		//接收用户选项
		cin >> select;
		if (select == 1)//申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)//查看自身预约
		{
			stu->showOrder();
		}
		else if (select == 3)//查看所有人预约
		{
			stu->showAllOrder();
		}
		else if (select == 4)//取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;//销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//进入管理员子菜单界面
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->openMenu();
		//将父类指针转为子类指针
		Manager* man = (Manager*)manager;
		int select = 0;
		//接收用户选项
		cin >> select;
		if (select == 1)//添加账号
		{
			//cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)//查看账号
		{
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)//查看机房
		{
			//cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4)//清空预约
		{
			//cout << "清空预约" << endl;
			man->clearFile();
		}
		else
		{
			delete manager;//销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//登录功能
void LoginIn(string fileName, int type)
{
	//父类指针  用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName,ios::in);
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;
	//判断身份
	if (type == 1)//学生
	{
		cout << "请输入你的学号:" << endl;
		cin >> id;
	}
	else if(type==2)//老师
	{
		cout << "请输入你的职工号:" << endl;
		cin >> id;
	}
	cout << "请输入用户名:" << endl;
	cin >> name;
	cout << "请输入密码:" << endl;
	cin >> pwd;
	int fId;//从文件中读取的id
	string fName;//从文件中读取的名字
	string fPwd;//从文件中读取的密码
	if (type == 1)
	{
		//学生
		while (ifs>>fId&&ifs>>fName&&ifs>>fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,pwd);
				//进入学生身份的子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "老师验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入老师身份的子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员的子菜单
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败" << endl;
	system("pause");
	system("cls");
	return;
}
int main()
{
	int select;
	while (true)
	{
		cout << "================欢迎来到机房预约系统================" << endl;
		cout << endl << "请输入你的身份" << endl;
		cout << "\t\t---------------------\n";
		cout << "\t\t|                   |\n";
		cout << "\t\t|     1.学生代表    |\n";
		cout << "\t\t|                   |\n";
		cout << "\t\t|     2.老    师    |\n";
		cout << "\t\t|                   |\n";
		cout << "\t\t|     3.管 理 员    |\n";
		cout << "\t\t|                   |\n";
		cout << "\t\t|     0.退    出    |\n";
		cout << "\t\t|                   |\n";
		cout << "\t\t---------------------\n";
		cout << "请输入你的选择:";
		cin >> select;
		switch (select)
		{
		case 1://学生代表
			LoginIn(STUDENT_FILE,1);
			break;
		case 2://老师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误,请重新输入!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}