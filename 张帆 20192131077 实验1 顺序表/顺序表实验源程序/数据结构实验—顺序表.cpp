#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream> 
#include <algorithm>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int locat = -1;    //����ҵ���Ԫ�ص�λ�� 
const int defaultSize = 1000;    //Ĭ�ϴ�С 

template <class T>
class SeqList
{
	protected:
		T *data;          //������� 
	    int last;         //��ǰ�Ѵ��������λ�� 
	    int maxSize;      //�������ɱ�������� 
		void reSize(int newSize);     //�ı�data����Ŀռ��С 
	    
	public:
		SeqList(int sz = defaultSize);        //���캯�� 
		SeqList(SeqList<T>& L);               //���ƹ��캯�� 
		~SeqList()                            //�������� 
		{
			delete[] data;                
		}
		int Size()const{return maxSize;}      //������������ɱ������ 
		int Length()const{return last + 1;}   //������� 
		bool Search(T& x)const;                //����x�Ƿ��ڱ��ڣ�����λ�ý��б�� 
		int Locate(int i)const;               //��λ��i������������ر������ 
		bool getData(int i, T& x)const        //ȡ��i�������ֵ 
		{
			if(i > 0 && i <= last + 1)
			{
				x = data[i - 1];
				return true; 
			}
			else return false;
		}
		bool Insert(int i, T& x);             //����x�ڵ�i������ 
		bool Remove(int i, T& x);             //ɾ����i�����ͨ��x���ر����ֵ 
		bool IsEmpty()const{return (last == -1) ? true : false;}  //�б�շ񣬿��򷵻�true�����򷵻�false 
		bool IsFull()const{return (last == maxSize - 1) ? true : false;} //�б��������򷵻�true�����򷵻�false 
		void input();                        //���� 
		void output();                       //��� 
		void infile(); 
		void outfile();
};

template <class T>
SeqList<T>::SeqList(int sz)    //���캯�� 
{
	if (sz > 0)
	{
		maxSize = sz;
		last = -1;        //�ñ��ʵ�ʳ���Ϊ�� 
		data = new T[maxSize];   //����˳���洢���� 
		if (data == NULL)     //��̬�ڴ����ʧ�� 
		{
			cerr << "�洢�������" << endl;
			exit(1); 
		}
	}
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L)//���ƹ��캯�� 
{
	maxSize = L.Size();
	last = L.Length() - 1;
	T value;
	data = new T[maxSize];
	if (data == NULL)      //��̬�ڴ����ʧ��
	{
		cerr << "�洢�������" << endl;
		exit(1); 
	}
	for (int i = 1; i <= last + 1; i++)
	{
		L.getData(i, value);
		data[i - 1] = value;
	}
}

template <class T>
void SeqList<T>::reSize(int newSize)//˽�к���������˳���Ĵ洢����ռ��СΪnewSize 
{
	if (newSize <= 0)
	{
		cerr << "��Ч�������С" << endl;
		return; 
	}
	if (newSize != maxSize)    //�޸� 
	{ 
		T * newarray = new T[newSize];   //���������� 
		if (newarray == NULL)
		{
			cerr << "�洢�������" << endl;
			exit(1); 
		}
		int n = last + 1;
		T* srcptr = data;     //ԭ�����׵�ַ 
		T* destptr = newarray;   //Ŀ�������׵�ַ 
		while(n--)  *destptr++ = *srcptr++;    //���� 
		delete[] data;    //ɾ�������� 
		data = newarray;  //���������� 
		maxSize = newSize;  
	}
}

template <class T>
bool SeqList<T>::Search(T& x)const//����������xֵ 
{
	for (int i = 0; i <= last; i++)
	{
		if (data[i] == x)
		{
			locat = i + 1;//���λ�� 
			return 1;
		}
	}
	return 0;
}

template <class T>
int SeqList<T>::Locate(int i)const//��λ��i������ 
{
	if (i >= 1 && i <= last + 1)  return i;
	else return 0;
}

template <class T>
bool SeqList<T>::Insert(int i, T& x)//����Ԫ��x���뵽˳����i��֮�����ɹ�����true,�����ɹ�����false 
{
	if (last == maxSize - 1)  return false;     //���������ܲ��� 
	if (i < 0 || i > last + 1)  return false;   //����i���������ܲ��� 
	for (int j = last; j >= i; j--)            
	{
		data[j + 1] = data[j];                  //���κ��ƣ��ճ���i��λ�� 
	}
	data[i] = x;                                //���� 
	last++;                                     //���λ�ü�1 
	return true;                                //����ɹ� 
}

template <class T>
bool SeqList<T>::Remove(int i, T& x)//ɾ��˳����i�����ͨ�������Ͳ���x����ɾ����Ԫ��ֵ����������ɾ���ɹ�����Ϣ����ɾ���ɹ��򷵻�true,���򷵻�false 
{
	if (last == -1)  return false;             //��գ�����ɾ�� 
	if (i < 1 || i > last + 1)  return false;  //����i����������ɾ�� 
	x = data[i - 1];                           //�汻ɾԪ�ص�ֵ 
	for (int j = i; j <= last; j++)
	{
		data[j - 1] = data[j];                 //����ǰ�ƣ�� 
	}
	last--;                                    //���λ��1 
	return true;                               //ɾ���ɹ� 
}

template <class T>
void SeqList<T>::input()
{
	cout << "��ʼ����˳������������Ԫ�ظ�����";
	while(1)
	{
		cin >> last;     //����Ԫ�����λ�� 
		if (last <= maxSize - 1)  break;    
		cout << "��Ԫ�ظ����������󣬷�Χ���ܳ���" << maxSize - 1 << ":"; 
	}
	for (int i = 0; i < last; i++)
	{
		cout << "�������" << i + 1 << "��Ԫ�أ�";  
		cin >> data[i];
	}
}

template <class T>
void SeqList<T>::output()
{
	for (int i = 0; i < last; i++)
	{
		cout << "#" << i + 1 << ":" << data[i] << " ";
	}
	cout << endl;
}

template <class T>
void SeqList<T>::infile()
{
	int len;    //���� 
	ifstream ifile;
	ifile.open("in.txt",ios::in);
	ifile >> len;
	{
		if (len > maxSize - 1)    
		{
			cout << "��Ԫ�ظ����������󣬷�Χ���ܳ���" << maxSize - 1 << ":"; 
			exit(1);
		}
	}
	for(int i = 0; i < len; i++)
	{
		ifile >> data[i];     //����
	}	 
	last = len;
	ifile.close();
}

template <class T>
void SeqList<T>::outfile()
{
	ofstream ofile;
	ofile.open("out.txt",ios::out);
	ofile << last << " ";
	for(int i = 0; i < last; i++)
	{
		ofile << data[i] << " ";
	}
	ofile.close();
}

void Menu()
{	
	SeqList<int> q;
	while(1)
	{
		cout << "*****************************" << endl;
		cout << "*-----���ݽṹʵ��˳���----*" << endl;
		cout << "*1����ʼ��  2������  3��ɾ��*" << endl;
		cout << "*     4������    5���˳�    *" << endl;
		cout << "*  6���ļ����� 7���ļ����  *" << endl;
		cout << "*****************************" << endl;
		cout << "��ѡ��";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			q.input();
			q.output();
			cout << "��ʼ���ɹ���" << endl; 
		}
		else if (choice == 2)
		{
			cout << "����ǰ��˳���Ϊ��" << endl;
			q.output();
			int ans, insertlocation;
			cout << "���������λ��Ϊ��";
			cin >>  insertlocation;
			cout << "���������Ԫ��ֵ��";
			cin >> ans;
			if(q.Insert(insertlocation, ans))
			{
				cout << "����ɹ���" << endl;
			}
			else cout << "����ʧ�ܣ�" << endl;
			cout << "������˳���Ϊ��" << endl;
			q.output();
		}
		else if (choice == 3)
		{
			cout << "ɾ��ǰ��˳���Ϊ��" << endl;
			q.output();
			int ans, removelocation;
			cout << "������ɾ��λ��Ϊ��";
			cin >> removelocation;
			if(q.Remove(removelocation, ans))
			{
				cout << "ɾ���ɹ���,ɾ����Ԫ��ֵΪ" << ans << endl; 
			}
			else cout << "ɾ��ʧ�ܣ�" << endl;
			cout << "ɾ�����˳���Ϊ��" << endl;
			q.output();
		}
		else if (choice == 4)
		{
			int ans;
			cout << "������Ҫ���ҵ�Ԫ��ֵ��";
			cin >> ans;
			if(q.Search(ans))
			{
				cout << "Ԫ��λ��Ϊ��" << locat << endl;
			}
			else cout << "δ�ҵ���Ԫ�أ�" << endl;
		}
		else if (choice == 6)
		{
			q.infile();
			cout << "�����˳���Ϊ��" << endl;
			q.output();
		}
		else if (choice == 7)
		{
			q.outfile();
			cout << "������ļ��ɹ���" << endl;
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
