#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int location = -1;    //���Ҫ���ҵ�λ��  

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
			first = new LinkNode<T>;       //���캯�� 
		}   
		List(const T& x)
		{
			first = new LinkNode<T>(x);    //���캯�� 
		}                  
		List(List<T>& L);                  //���ƹ��캯�� 
		~List()                            //�������� 
		{
			makeEmpty();                
		}
		void makeEmpty();                  //��������Ϊ�ձ� 
		int Length()const;                 //����������
		LinkNode<T>* getHead()const
		{
			return first;                  //���ظ���ͷ�ڵ��ַ
		}
		bool Search(T x);                   //����������x��Ԫ�� 
		LinkNode<T>* Locate(int i);        //������i��Ԫ�صĵ�ַ 
		bool getData(int i, T& x)const;    //ȡ����i��Ԫ�ص�ֵ
		void setData(int i, T& x);         //��x�޸ĵ�i��Ԫ�ص�ֵ 
		bool Insert(int i, T& x);          //����x�ڵ�i������� 
		bool Remove(int i, T& x);          //ɾ����i�����ͨ��x���ر����ֵ 
		bool IsEmpty()const{return first->link == NULL ? true : false;}  //�б�շ񣬿��򷵻�true
		bool IsFull()const{return false;}  //�б��������򷵻�true 
		void input();                      //���� 
		void output();                     //���
		void ReverseList();                //��������
		void ResolveList();                //����ֽ�
		void inputFront();         //ǰ�巨����������
		void inputRear();          //��巨����������
};

template <class T>
List<T>::List(List<T>& L)
{
	T value;
	LinkNode<T> *srcptr = L.getHead();    //�����Ʊ�ĸ���ͷ�ڵ��ַ 
	LinkNode<T> *destptr = first = new LinkNode<T>;
	while(srcptr->link != NULL)   //����ڵ㸴�� 
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

template <class T>
void List<T>::makeEmpty()   //��������Ϊ�ձ�  
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
int List<T>::Length()const   //��� 
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
bool List<T>::Search(T x)   //�ڱ�������������x�Ľڵ� 
{
	
	LinkNode<T> * current = first->link;
	while (current != NULL)  
	{
		if (current->data == x)
		{
			return true; 
			break;       //ѭ���Һ�x�ڵ�
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
LinkNode<T> *List<T>::Locate(int i)  //��λ���������ر��е�i��Ԫ�صĵ�ַ 
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
bool List<T>::getData(int i, T& x)const  //ȡ�������е�i��Ԫ�ص�ֵ 
{
	if (i <= 0)  return NULL;    //iֵ̫С 
	LinkNode<T> * current = Locate(i);
	if (current == NULL)  return false;     //iֵ̫�� 
	else
	{
		x = current->data;
		return true;
	}
}

template <class T>
void List<T>::setData(int i, T& x)  //�������е�i��Ԫ�ظ�ֵx 
{
	if (i <= 0)  return;    //iֵ̫С
	LinkNode<T> *current = Locate(i);
	if (current == NULL)  return;
	else current->data = x; 
}

template <class T>
bool List<T>::Insert(int i, T& x)  //����Ԫ��x�����������е�i���ڵ�֮�� 
{
	LinkNode<T> *current = Locate(i);
	if (current == NULL)  return false;
	LinkNode<T> *newNode = new LinkNode<T>(x);
	if (newNode == NULL)
	{
		cerr << "�洢�������" << endl;
		exit(1); 
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template <class T>
bool List<T>::Remove(int i, T& x)  //���������е�i��Ԫ��ɾȥ 
{
	LinkNode<T> *current = Locate(i - 1);
	if(current == NULL || current->link == NULL)  return false; //ɾ��ʧ�� 
	LinkNode<T> *del = current->link;  //��������������ɾ�ڵ������ժ��
	current->link = del->link;
	x = del->data;
	delete del;
	return true; 
}

template <class T>
void List<T>::inputFront()    //ǰ�巨���������� 
{
	T val;
	int i = 0, num;
	LinkNode<T> *newNode;
	makeEmpty();         
	cout << "������Ԫ�ظ�����";
	cin >> num;
	while(i != num)    
	{
		cout << "�������" << i + 1 << "��Ԫ�أ�"; 
		cin >> val;
		newNode = new LinkNode<T>(val);   //�����½ڵ�
		if (newNode == NULL)
		{
			cerr << "�洢�������" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		i++;
	}
}

template <class T>
void List<T>::inputRear()    //��巨���������� 
{
	T val;
	int i = 0, num;
	cout << "������Ԫ�ظ�����";
	cin >> num;
	LinkNode<T> *newNode, *last;  //lastָ���β 
	makeEmpty();
	last = first;
	while(i != num)
	{
		cout << "�������" << i + 1 << "��Ԫ�أ�"; 
		cin >> val;
		newNode = new LinkNode<T>(val);   //�����½ڵ�
		if (newNode == NULL)
		{
			cerr << "�洢�������" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		i++;
	}
	last->link = NULL;   //����β 
}

template <class T>
void List<T>::ReverseList()    //�������� 
{
	LinkNode<T>* temp = first->link;
	LinkNode<T>* p1 = temp;
	LinkNode<T>* p2 = p1->link;
	LinkNode<T>* p3 = p2->link;
	while (p3->link != NULL)
	{
		p2->link = p1;
		p1 = p2;      //�������� 
		p2 = p3;
		p3 = p3->link;
	}
	p2->link = p1;
	p3->link = p2;
	first->link = p3;
	temp->link = NULL;
}

template <class T>
void List<T>::ResolveList()   //����ֽ�
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
	cout << "����1Ϊ��" << endl;
	while(head1 != NULL)
	{
		cout << head1->data << " ";
		head1 = head1->link;
	}
	cout << endl;
	cout << "����2Ϊ��" << endl;
	while(head2 != NULL)
	{
		cout << head2->data << " ";
		head2 = head2->link;
	}
}

template <class T>
void List<T>::output()      //��ӡ 
{
	int i = 1;
	LinkNode<T> *current = first->link;
	while(current != NULL)
	{
		cout << "��" << i << "��Ԫ��Ϊ��" << current-> data << endl;
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
		cout << "*-------���ݽṹʵ������------*" << endl;
		cout << "*1����ʼ��   2������   3������*" << endl;
		cout << "*4��ɾ��  5������  6�������*" << endl;
		cout << "*7��������  8����ֽ�  9���˳�*" << endl;
		cout << "*******************************" << endl;
		cout << "��ѡ��"; 
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			list.makeEmpty();
			cout << "��ʼ���ɹ���" << endl;
		}
		else if (choice == 2)
		{
			cout << "��ѡ������ʽ��1��ǰ�巨     2����巨" << endl;
			int rain;  cin >> rain;
			if (rain == 1)
			{
				list.inputFront();
			}
			else list.inputRear();
			cout << "�����ɹ���" << endl;
			list.output();
		}
		else if (choice == 3)
		{
			int insertlocation, num;
			cout << "Ҫ�����ֵΪ��";
			cin >> num;
			cout << "Ҫ�����λ��Ϊ��";
			cin >> insertlocation;
			cout << "����֮ǰ������Ϊ��" << endl;
			list.output();
			if (list.Insert(insertlocation, num))
			{
				cout << "����ɹ���,����������Ϊ��" << endl;
				list.output();
			}
			else cout << "����ʧ�ܣ�" << endl;
		}
		else if (choice == 4)
		{
			int removelocation, num;
			cout << "Ҫɾ����λ��Ϊ��";
			cin >> removelocation;
			cout << "ɾ��֮ǰ������Ϊ��" << endl;
			list.output();
			if (list.Remove(removelocation, num))
			{
				cout << "ɾ���ɹ���ɾ���������Ϊ��" << endl;
				list.output(); 
			}
			else cout << "ɾ��ʧ�ܣ�" << endl; 
		}
		else if (choice == 5)
		{
			int num;
			cout << "Ҫ���ҵ�Ԫ��ֵΪ��";
			cin >> num;
			if (list.Search(num))
			{
				cout << "Ԫ�ش��ڣ�    Ԫ�ص�λ��Ϊ��" << location + 2 << "��" << endl;
			}
			else cout << "Ԫ�ز����ڣ�" << endl;
			location = -1;      //λ�ó�ʼ�� 
		}
		else if (choice == 6)
		{
			cout << "����ĳ���Ϊ" << list.Length() << endl; 
		}
		else if (choice == 7)
		{
			cout << "����ǰ������Ϊ��" << endl;
			list.output(); 
			list.ReverseList();
			cout << "�������óɹ���,���ú������Ϊ��" << endl;
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
