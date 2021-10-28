#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream> 
#include <algorithm>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int locat = -1;    //标记找到的元素的位置 
const int defaultSize = 1000;    //默认大小 

template <class T>
class SeqList
{
	protected:
		T *data;          //存放数组 
	    int last;         //当前已存表项的最后位置 
	    int maxSize;      //最大可容纳表项的项数 
		void reSize(int newSize);     //改变data数组的空间大小 
	    
	public:
		SeqList(int sz = defaultSize);        //构造函数 
		SeqList(SeqList<T>& L);               //复制构造函数 
		~SeqList()                            //析构函数 
		{
			delete[] data;                
		}
		int Size()const{return maxSize;}      //计算表最大可容纳表项个数 
		int Length()const{return last + 1;}   //计算表长度 
		bool Search(T& x)const;                //搜索x是否在表内，并对位置进行标记 
		int Locate(int i)const;               //定位第i个表项，函数返回表项序号 
		bool getData(int i, T& x)const        //取第i个表象的值 
		{
			if(i > 0 && i <= last + 1)
			{
				x = data[i - 1];
				return true; 
			}
			else return false;
		}
		bool Insert(int i, T& x);             //插入x在第i个表项 
		bool Remove(int i, T& x);             //删除第i个表项，通过x返回表项的值 
		bool IsEmpty()const{return (last == -1) ? true : false;}  //判表空否，空则返回true，否则返回false 
		bool IsFull()const{return (last == maxSize - 1) ? true : false;} //判表满否，满则返回true，否则返回false 
		void input();                        //输入 
		void output();                       //输出 
		void infile(); 
		void outfile();
};

template <class T>
SeqList<T>::SeqList(int sz)    //构造函数 
{
	if (sz > 0)
	{
		maxSize = sz;
		last = -1;        //置表的实际长度为空 
		data = new T[maxSize];   //创建顺序表存储数组 
		if (data == NULL)     //动态内存分配失败 
		{
			cerr << "存储分配错误！" << endl;
			exit(1); 
		}
	}
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L)//复制构造函数 
{
	maxSize = L.Size();
	last = L.Length() - 1;
	T value;
	data = new T[maxSize];
	if (data == NULL)      //动态内存分配失败
	{
		cerr << "存储分配错误！" << endl;
		exit(1); 
	}
	for (int i = 1; i <= last + 1; i++)
	{
		L.getData(i, value);
		data[i - 1] = value;
	}
}

template <class T>
void SeqList<T>::reSize(int newSize)//私有函数：扩充顺序表的存储数组空间大小为newSize 
{
	if (newSize <= 0)
	{
		cerr << "无效的数组大小" << endl;
		return; 
	}
	if (newSize != maxSize)    //修改 
	{ 
		T * newarray = new T[newSize];   //建立新数组 
		if (newarray == NULL)
		{
			cerr << "存储分配错误" << endl;
			exit(1); 
		}
		int n = last + 1;
		T* srcptr = data;     //原数组首地址 
		T* destptr = newarray;   //目的数组首地址 
		while(n--)  *destptr++ = *srcptr++;    //复制 
		delete[] data;    //删除老数组 
		data = newarray;  //复制新数组 
		maxSize = newSize;  
	}
}

template <class T>
bool SeqList<T>::Search(T& x)const//搜索给定的x值 
{
	for (int i = 0; i <= last; i++)
	{
		if (data[i] == x)
		{
			locat = i + 1;//标记位置 
			return 1;
		}
	}
	return 0;
}

template <class T>
int SeqList<T>::Locate(int i)const//定位第i个表项 
{
	if (i >= 1 && i <= last + 1)  return i;
	else return 0;
}

template <class T>
bool SeqList<T>::Insert(int i, T& x)//将新元素x插入到顺序表第i项之后，若成功返回true,若不成功返回false 
{
	if (last == maxSize - 1)  return false;     //表满，不能插入 
	if (i < 0 || i > last + 1)  return false;   //参数i不合理，不能插入 
	for (int j = last; j >= i; j--)            
	{
		data[j + 1] = data[j];                  //依次后移，空出第i号位置 
	}
	data[i] = x;                                //插入 
	last++;                                     //最后位置加1 
	return true;                                //插入成功 
}

template <class T>
bool SeqList<T>::Remove(int i, T& x)//删除顺序表第i个表项，通过引用型参数x返回删除的元素值，函数返回删除成功的信息，若删除成功则返回true,否则返回false 
{
	if (last == -1)  return false;             //表空，不能删除 
	if (i < 1 || i > last + 1)  return false;  //参数i不合理，不能删除 
	x = data[i - 1];                           //存被删元素的值 
	for (int j = i; j <= last; j++)
	{
		data[j - 1] = data[j];                 //依次前移，填补 
	}
	last--;                                    //最后位减1 
	return true;                               //删除成功 
}

template <class T>
void SeqList<T>::input()
{
	cout << "开始建立顺序表，请输入表中元素个数：";
	while(1)
	{
		cin >> last;     //输入元素最后位置 
		if (last <= maxSize - 1)  break;    
		cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << ":"; 
	}
	for (int i = 0; i < last; i++)
	{
		cout << "请输入第" << i + 1 << "个元素：";  
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
	int len;    //长度 
	ifstream ifile;
	ifile.open("in.txt",ios::in);
	ifile >> len;
	{
		if (len > maxSize - 1)    
		{
			cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << ":"; 
			exit(1);
		}
	}
	for(int i = 0; i < len; i++)
	{
		ifile >> data[i];     //读入
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
		cout << "*-----数据结构实验顺序表----*" << endl;
		cout << "*1、初始化  2、插入  3、删除*" << endl;
		cout << "*     4、查找    5、退出    *" << endl;
		cout << "*  6、文件读入 7、文件输出  *" << endl;
		cout << "*****************************" << endl;
		cout << "请选择：";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			q.input();
			q.output();
			cout << "初始化成功！" << endl; 
		}
		else if (choice == 2)
		{
			cout << "插入前的顺序表为：" << endl;
			q.output();
			int ans, insertlocation;
			cout << "请输入插入位置为：";
			cin >>  insertlocation;
			cout << "请输入插入元素值：";
			cin >> ans;
			if(q.Insert(insertlocation, ans))
			{
				cout << "插入成功！" << endl;
			}
			else cout << "插入失败！" << endl;
			cout << "插入后的顺序表为：" << endl;
			q.output();
		}
		else if (choice == 3)
		{
			cout << "删除前的顺序表为：" << endl;
			q.output();
			int ans, removelocation;
			cout << "请输入删除位置为：";
			cin >> removelocation;
			if(q.Remove(removelocation, ans))
			{
				cout << "删除成功！,删除的元素值为" << ans << endl; 
			}
			else cout << "删除失败！" << endl;
			cout << "删除后的顺序表为：" << endl;
			q.output();
		}
		else if (choice == 4)
		{
			int ans;
			cout << "请输入要查找的元素值：";
			cin >> ans;
			if(q.Search(ans))
			{
				cout << "元素位置为：" << locat << endl;
			}
			else cout << "未找到此元素！" << endl;
		}
		else if (choice == 6)
		{
			q.infile();
			cout << "读入的顺序表为：" << endl;
			q.output();
		}
		else if (choice == 7)
		{
			q.outfile();
			cout << "输出到文件成功！" << endl;
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
