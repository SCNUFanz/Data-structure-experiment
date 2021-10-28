#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MaxSize = 100;

template <class T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T> *ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};

template <class T>
class LinkedQueue
{
	public:
		LinkNode<T> *front,  *rear;           
		
	public:
		LinkedQueue(): rear(NULL), front(NULL){}   //构造函数
		bool EnQueue(const T& x);                  //将x加入队列中 
		bool DeQueue(T& x);                        //删除队头元素,x返回其值
		bool IsEmpty()const{return (front == NULL) ? true : false;}  //判队空否
		void Display();   //打印 
		int Location();   //返回位置 
};

template <class T>
bool LinkedQueue<T>::EnQueue(const T& x)  //将x加入队列中
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x); 
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		rear = rear->link;
	}
	return true;
}

template <class T>
bool LinkedQueue<T>::DeQueue(T& x)   //删除队头元素 
{
	if (IsEmpty() == true)  return false;
	LinkNode<T> *p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <class T>
void LinkedQueue<T>::Display()      //打印 
{
	if (IsEmpty() == true)
	{
		cout << "便道上没有停汽车！" << endl;
		return;
	} 
	LinkNode<T> *cur = front;
	cout << "现在停在便道上的汽车为：" << endl;
	while (cur != NULL)
	{
		cout << "车牌号为" << cur->data << "的汽车" << endl;
		cur = cur->link;
	}
}

template <class T>
int LinkedQueue<T>::Location()    //求汽车在便道的位置 
{
	int locat = 0;
	LinkNode<T> *cur = front;
	while (cur != NULL)
	{
		locat++;
		cur = cur->link;
	}
	return locat;
}


class SeqStack
{
	public:
		int *hour;     //达到小时 
		int *second;   //达到分钟 
		string *name;  //车牌号 
		int top;       //栈顶指针 
		int maxSize;
		 
	public:
		SeqStack(int sz = 50);         //建立一个空栈 
		~SeqStack()                    //析构函数 
		{
			delete[] hour;
			delete[] second;
			delete[] name;
		}
		void Push(int Hour, int Second, string Name);      //插入
		void Pop(int& Hour, int& Second, string& Name);    //删除栈顶元素 
		bool IsEmpty()const {return(top == -1) ? true : false;}   //判空 
		bool IsFull()const {return (top == maxSize - 1) ? true : false;} //判满 
		void Print();  //打印 
};

SeqStack::SeqStack(int sz): top(-1), maxSize(sz)
{
	hour = new int[maxSize];               //创建栈的数组空间 
	second = new int[maxSize];
	name = new string[maxSize];
}

void SeqStack::Push(int Hour, int Second, string Name)  //进栈 
{
	hour[++top] = Hour;                    //栈顶指针先加一，再进栈
	second[top] = Second;                  
	name[top] = Name;                     
}

void SeqStack::Pop(int& Hour, int& Second, string& Name) //出栈 
{
	Hour = hour[top];
	Second = second[top];
	Name = name[top];
	top--;
}

void SeqStack::Print()
{
	int num = top; 
	if (IsEmpty())    
	{
		cout << "停车场为空！！！" << endl;     
		return;
	} 
	cout << "现在停在停车场的汽车为：" << endl; 
	while (num != -1)
	{
		cout << "车牌号为" << name[num] << "的汽车" << endl;
		num--;
	}
}



void Menu()
{
	int n;
	cout << "请输入停车场容量：";
	cin >> n;
	SeqStack Now(n);
	SeqStack Temp(n);
	LinkedQueue<string> Place;
	while(1)
	{
		int choice;
		cout << "*********停车场管理系统********" << endl;
		cout << "*         1、汽车到达         *" << endl;
		cout << "*         2、汽车离开         *" << endl;
		cout << "*3、输出停车场中的所有汽车牌号*" << endl;
		cout << "*4、输出候车场中的所有汽车牌号*" << endl;
		cout << "*       5、退出系统运行       *" << endl;
		cout << "*******************************" << endl;
		cout << "请输入要操作的选项：";
		cin >> choice;
		if (choice == 1)
		{
			int Hour, Second;
			string Car_Name;
			cout << "请依次输入汽车的车牌号  达到小时  达到分钟：";
			cin >> Car_Name >> Hour >> Second;
			if (Now.IsFull())
			{
				Place.EnQueue(Car_Name);
				cout << "车牌号为" << Car_Name << "的汽车在便道停车的位置为：" << Place.Location() << endl;
			}
			else
			{
				Now.Push(Hour, Second, Car_Name);
				cout << "车牌号为" << Car_Name << "的汽车在停车场停车的位置为：" <<  Now.top + 1 << endl; 
			}
		}
		else if (choice == 2)
		{
			string left_Car, Name, get_Car;
			int left_hour, left_second, Hour, Second, get_hour, get_second;
			cout << "请输入要离开的汽车的车牌号  离开小时  离开分钟：";
			cin >> left_Car >> left_hour >> left_second;
			while (Now.top != -1)
			{
				Now.Pop(Hour, Second, Name);
				if (Name != left_Car)
				{
					Temp.Push(Hour, Second, Name);     //将车辆移到临时栈 
				}
				else
				{
					double Car_time = left_hour * 60 + left_second - Hour * 60 - Second;     //停留分钟 
					cout << "车牌号为：" << left_Car << "的汽车停车时长为：" << Car_time << "分钟，";
					cout << "停车费为：" << ceil(Car_time / 60) * 3 << "元" << endl;
					while (Temp.top != -1)     //将车辆移回停车场 
					{
						Temp.Pop(get_hour, get_second, get_Car);
						Now.Push(get_hour, get_second, get_Car);
					}
					if (!Place.IsEmpty())    //便道的车可以进入 
					{
						string new_Car;
						Place.DeQueue(new_Car);
						Now.Push(left_hour, left_second, new_Car);
					}
					break;
				}
				if (Now.top == -1)    //找不到此车辆
				{
					cout << "没有此车辆！！！" << endl;
					while (Temp.top != -1)
					{
						Temp.Pop(get_hour, get_second, get_Car);
						Now.Push(get_hour, get_second, get_Car);
					}
					break;
				}
			}
		}
		else if (choice == 3)
		{
			Now.Print();
		}
		else if (choice == 4)
		{
			Place.Display();
		}
		else break;
		cout << endl << endl;
	}
}


int main(int argc, char** argv)
{
	Menu();    //主菜单 
	return 0;
}
