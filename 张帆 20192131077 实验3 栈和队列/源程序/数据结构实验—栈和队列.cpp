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
		LinkedQueue(): rear(NULL), front(NULL){}   //���캯��
		bool EnQueue(const T& x);                  //��x��������� 
		bool DeQueue(T& x);                        //ɾ����ͷԪ��,x������ֵ
		bool IsEmpty()const{return (front == NULL) ? true : false;}  //�жӿշ�
		void Display();   //��ӡ 
		int Location();   //����λ�� 
};

template <class T>
bool LinkedQueue<T>::EnQueue(const T& x)  //��x���������
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
bool LinkedQueue<T>::DeQueue(T& x)   //ɾ����ͷԪ�� 
{
	if (IsEmpty() == true)  return false;
	LinkNode<T> *p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <class T>
void LinkedQueue<T>::Display()      //��ӡ 
{
	if (IsEmpty() == true)
	{
		cout << "�����û��ͣ������" << endl;
		return;
	} 
	LinkNode<T> *cur = front;
	cout << "����ͣ�ڱ���ϵ�����Ϊ��" << endl;
	while (cur != NULL)
	{
		cout << "���ƺ�Ϊ" << cur->data << "������" << endl;
		cur = cur->link;
	}
}

template <class T>
int LinkedQueue<T>::Location()    //�������ڱ����λ�� 
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
		int *hour;     //�ﵽСʱ 
		int *second;   //�ﵽ���� 
		string *name;  //���ƺ� 
		int top;       //ջ��ָ�� 
		int maxSize;
		 
	public:
		SeqStack(int sz = 50);         //����һ����ջ 
		~SeqStack()                    //�������� 
		{
			delete[] hour;
			delete[] second;
			delete[] name;
		}
		void Push(int Hour, int Second, string Name);      //����
		void Pop(int& Hour, int& Second, string& Name);    //ɾ��ջ��Ԫ�� 
		bool IsEmpty()const {return(top == -1) ? true : false;}   //�п� 
		bool IsFull()const {return (top == maxSize - 1) ? true : false;} //���� 
		void Print();  //��ӡ 
};

SeqStack::SeqStack(int sz): top(-1), maxSize(sz)
{
	hour = new int[maxSize];               //����ջ������ռ� 
	second = new int[maxSize];
	name = new string[maxSize];
}

void SeqStack::Push(int Hour, int Second, string Name)  //��ջ 
{
	hour[++top] = Hour;                    //ջ��ָ���ȼ�һ���ٽ�ջ
	second[top] = Second;                  
	name[top] = Name;                     
}

void SeqStack::Pop(int& Hour, int& Second, string& Name) //��ջ 
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
		cout << "ͣ����Ϊ�գ�����" << endl;     
		return;
	} 
	cout << "����ͣ��ͣ����������Ϊ��" << endl; 
	while (num != -1)
	{
		cout << "���ƺ�Ϊ" << name[num] << "������" << endl;
		num--;
	}
}



void Menu()
{
	int n;
	cout << "������ͣ����������";
	cin >> n;
	SeqStack Now(n);
	SeqStack Temp(n);
	LinkedQueue<string> Place;
	while(1)
	{
		int choice;
		cout << "*********ͣ��������ϵͳ********" << endl;
		cout << "*         1����������         *" << endl;
		cout << "*         2�������뿪         *" << endl;
		cout << "*3�����ͣ�����е����������ƺ�*" << endl;
		cout << "*4������򳵳��е����������ƺ�*" << endl;
		cout << "*       5���˳�ϵͳ����       *" << endl;
		cout << "*******************************" << endl;
		cout << "������Ҫ������ѡ�";
		cin >> choice;
		if (choice == 1)
		{
			int Hour, Second;
			string Car_Name;
			cout << "���������������ĳ��ƺ�  �ﵽСʱ  �ﵽ���ӣ�";
			cin >> Car_Name >> Hour >> Second;
			if (Now.IsFull())
			{
				Place.EnQueue(Car_Name);
				cout << "���ƺ�Ϊ" << Car_Name << "�������ڱ��ͣ����λ��Ϊ��" << Place.Location() << endl;
			}
			else
			{
				Now.Push(Hour, Second, Car_Name);
				cout << "���ƺ�Ϊ" << Car_Name << "��������ͣ����ͣ����λ��Ϊ��" <<  Now.top + 1 << endl; 
			}
		}
		else if (choice == 2)
		{
			string left_Car, Name, get_Car;
			int left_hour, left_second, Hour, Second, get_hour, get_second;
			cout << "������Ҫ�뿪�������ĳ��ƺ�  �뿪Сʱ  �뿪���ӣ�";
			cin >> left_Car >> left_hour >> left_second;
			while (Now.top != -1)
			{
				Now.Pop(Hour, Second, Name);
				if (Name != left_Car)
				{
					Temp.Push(Hour, Second, Name);     //�������Ƶ���ʱջ 
				}
				else
				{
					double Car_time = left_hour * 60 + left_second - Hour * 60 - Second;     //ͣ������ 
					cout << "���ƺ�Ϊ��" << left_Car << "������ͣ��ʱ��Ϊ��" << Car_time << "���ӣ�";
					cout << "ͣ����Ϊ��" << ceil(Car_time / 60) * 3 << "Ԫ" << endl;
					while (Temp.top != -1)     //�������ƻ�ͣ���� 
					{
						Temp.Pop(get_hour, get_second, get_Car);
						Now.Push(get_hour, get_second, get_Car);
					}
					if (!Place.IsEmpty())    //����ĳ����Խ��� 
					{
						string new_Car;
						Place.DeQueue(new_Car);
						Now.Push(left_hour, left_second, new_Car);
					}
					break;
				}
				if (Now.top == -1)    //�Ҳ����˳���
				{
					cout << "û�д˳���������" << endl;
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
	Menu();    //���˵� 
	return 0;
}
