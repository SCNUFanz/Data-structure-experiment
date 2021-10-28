#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int location = -1;    //标记要查找的位置  

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
class List
{
	public:
		LinkNode<T> *first;
		
	public:
		List()
		{
			first = new LinkNode<T>;       //构造函数 
		}   
		List(const T& x)
		{
			first = new LinkNode<T>(x);    //构造函数 
		}                  
		List(List<T>& L);                  //复制构造函数 
		~List()                            //析构函数 
		{
			makeEmpty();                
		}
		void makeEmpty();                  //将链表置为空表 
		int Length()const;                 //计算链表长度
		LinkNode<T>* getHead()const
		{
			return first;                  //返回附加头节点地址
		}
		bool Search(T x);                   //搜索含数据x的元素 
		LinkNode<T>* Locate(int i);        //搜索第i个元素的地址 
		bool getData(int i, T& x)const;    //取出第i个元素的值
		void setData(int i, T& x);         //用x修改第i个元素的值 
		bool Insert(int i, T& x);          //插入x在第i个表项后 
		bool Remove(int i, T& x);          //删除第i个表项，通过x返回表项的值 
		bool IsEmpty()const{return first->link == NULL ? true : false;}  //判表空否，空则返回true
		bool IsFull()const{return false;}  //判表满否，满则返回true 
		void input();                      //输入 
		void output();                     //输出
		void ReverseList();                //链表逆置
		void ResolveList();                //链表分解
		void inputFront();         //前插法建立单链表
		void inputRear();          //后插法建立单链表
};

template <class T>
List<T>::List(List<T>& L)
{
	T value;
	LinkNode<T> *srcptr = L.getHead();    //被复制表的附加头节点地址 
	LinkNode<T> *destptr = first = new LinkNode<T>;
	while(srcptr->link != NULL)   //逐个节点复制 
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

template <class T>
void List<T>::makeEmpty()   //将链表置为空表  
{
	LinkNode<T> *q;
	while(first->link != NULL)         
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

template <class T>
int List<T>::Length()const   //求表长 
{
	LinkNode<T> *p = first->link;
	int count = 0;
	while(p != NULL)
	{
		p = p->link;
		count++;
	} 
	return count;
}

template <class T>
bool List<T>::Search(T x)   //在表中搜索含数据x的节点 
{
	
	LinkNode<T> * current = first->link;
	while (current != NULL)  
	{
		if (current->data == x)
		{
			return true; 
			break;       //循链找含x节点
		}
		else
		{
			current = current->link;
			location++;
		}
	}
	return false;
}

template <class T>
LinkNode<T> *List<T>::Locate(int i)  //定位函数，返回表中第i个元素的地址 
{
	if (i < 0)  return NULL;
	LinkNode<T> *current = first;
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link;
		k++;
	}
	return current;
}

template <class T>
bool List<T>::getData(int i, T& x)const  //取出链表中第i个元素的值 
{
	if (i <= 0)  return NULL;    //i值太小 
	LinkNode<T> * current = Locate(i);
	if (current == NULL)  return false;     //i值太大 
	else
	{
		x = current->data;
		return true;
	}
}

template <class T>
void List<T>::setData(int i, T& x)  //给链表中第i个元素赋值x 
{
	if (i <= 0)  return;    //i值太小
	LinkNode<T> *current = Locate(i);
	if (current == NULL)  return;
	else current->data = x; 
}

template <class T>
bool List<T>::Insert(int i, T& x)  //将新元素x插入在链表中第i个节点之后 
{
	LinkNode<T> *current = Locate(i);
	if (current == NULL)  return false;
	LinkNode<T> *newNode = new LinkNode<T>(x);
	if (newNode == NULL)
	{
		cerr << "存储分配错误！" << endl;
		exit(1); 
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template <class T>
bool List<T>::Remove(int i, T& x)  //将新链表中第i个元素删去 
{
	LinkNode<T> *current = Locate(i - 1);
	if(current == NULL || current->link == NULL)  return false; //删除失败 
	LinkNode<T> *del = current->link;  //重新拉链，将被删节点从链中摘下
	current->link = del->link;
	x = del->data;
	delete del;
	return true; 
}

template <class T>
void List<T>::inputFront()    //前插法建立单链表 
{
	T val;
	int i = 0, num;
	LinkNode<T> *newNode;
	makeEmpty();         
	cout << "请输入元素个数：";
	cin >> num;
	while(i != num)    
	{
		cout << "请输入第" << i + 1 << "个元素："; 
		cin >> val;
		newNode = new LinkNode<T>(val);   //创建新节点
		if (newNode == NULL)
		{
			cerr << "存储分配错误！" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		i++;
	}
}

template <class T>
void List<T>::inputRear()    //后插法建立单链表 
{
	T val;
	int i = 0, num;
	cout << "请输入元素个数：";
	cin >> num;
	LinkNode<T> *newNode, *last;  //last指向表尾 
	makeEmpty();
	last = first;
	while(i != num)
	{
		cout << "请输入第" << i + 1 << "个元素："; 
		cin >> val;
		newNode = new LinkNode<T>(val);   //创建新节点
		if (newNode == NULL)
		{
			cerr << "存储分配错误！" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		i++;
	}
	last->link = NULL;   //表收尾 
}

template <class T>
void List<T>::ReverseList()    //链表逆置 
{
	LinkNode<T>* temp = first->link;
	LinkNode<T>* p1 = temp;
	LinkNode<T>* p2 = p1->link;
	LinkNode<T>* p3 = p2->link;
	while (p3->link != NULL)
	{
		p2->link = p1;
		p1 = p2;      //逐步往后移 
		p2 = p3;
		p3 = p3->link;
	}
	p2->link = p1;
	p3->link = p2;
	first->link = p3;
	temp->link = NULL;
}

template <class T>
void List<T>::ResolveList()   //链表分解
{
	LinkNode<T> *head1, *head2, *last;
	last = first;
	while(last->link != NULL)
	{
		if (int(last->link->data) % 2 != 0)
		{
			last = last->link;
		}
		else
		{
			head2 = last->link;
			last->link = NULL;
			break;
		}
	}
	LinkNode<T>* now = head2;
	while(now->link != NULL)
	{
		if (now->link->data % 2 != 0)
		{
			last->link = now->link;
			last = last->link;
		    now->link = last->link;
		    last->link = NULL;
		}
		else now = now->link;
	}
	head1 = first->link; 
	cout << "链表1为：" << endl;
	while(head1 != NULL)
	{
		cout << head1->data << " ";
		head1 = head1->link;
	}
	cout << endl;
	cout << "链表2为：" << endl;
	while(head2 != NULL)
	{
		cout << head2->data << " ";
		head2 = head2->link;
	}
}

template <class T>
void List<T>::output()      //打印 
{
	int i = 1;
	LinkNode<T> *current = first->link;
	while(current != NULL)
	{
		cout << "第" << i << "个元素为：" << current-> data << endl;
		current = current->link;
		i++;
	}
	cout << endl;
}

void Menu()
{
	List<int> list(0);
	while(1)
	{
		cout << "*******************************" << endl;
		cout << "*-------数据结构实验链表------*" << endl;
		cout << "*1、初始化   2、建链   3、插入*" << endl;
		cout << "*4、删除  5、查找  6、输出表长*" << endl;
		cout << "*7、表逆置  8、表分解  9、退出*" << endl;
		cout << "*******************************" << endl;
		cout << "请选择："; 
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			list.makeEmpty();
			cout << "初始化成功！" << endl;
		}
		else if (choice == 2)
		{
			cout << "请选择建链方式：1、前插法     2、后插法" << endl;
			int rain;  cin >> rain;
			if (rain == 1)
			{
				list.inputFront();
			}
			else list.inputRear();
			cout << "建链成功！" << endl;
			list.output();
		}
		else if (choice == 3)
		{
			int insertlocation, num;
			cout << "要插入的值为：";
			cin >> num;
			cout << "要插入的位置为；";
			cin >> insertlocation;
			cout << "插入之前的链表为：" << endl;
			list.output();
			if (list.Insert(insertlocation, num))
			{
				cout << "插入成功！,插入后的链表为：" << endl;
				list.output();
			}
			else cout << "插入失败！" << endl;
		}
		else if (choice == 4)
		{
			int removelocation, num;
			cout << "要删除的位置为：";
			cin >> removelocation;
			cout << "删除之前的链表为：" << endl;
			list.output();
			if (list.Remove(removelocation, num))
			{
				cout << "删除成功！删除后的链表为：" << endl;
				list.output(); 
			}
			else cout << "删除失败！" << endl; 
		}
		else if (choice == 5)
		{
			int num;
			cout << "要查找的元素值为：";
			cin >> num;
			if (list.Search(num))
			{
				cout << "元素存在！    元素的位置为第" << location + 2 << "个" << endl;
			}
			else cout << "元素不存在！" << endl;
			location = -1;      //位置初始化 
		}
		else if (choice == 6)
		{
			cout << "链表的长度为" << list.Length() << endl; 
		}
		else if (choice == 7)
		{
			cout << "逆置前的链表为：" << endl;
			list.output(); 
			list.ReverseList();
			cout << "链表逆置成功！,逆置后的链表为：" << endl;
			list.output();
		}
		else if (choice == 8)
		{
			list.ResolveList();
		}
		else break;
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	Menu();
	return 0;
}
