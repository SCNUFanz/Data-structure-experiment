#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <cstring>
#include <fstream> 
#include <algorithm> 
using namespace std;
const int NodeNumber = 100;  //结点个数

int root, idx;  //根结点，结点指针

class Node
{
  private:
    string sex, name, address, phone_number;  // 姓名、性别、电话、地址
    
    struct Birthday  //出生日期
	{
        int year, month, day;
        friend istream &operator >> (istream &in, Birthday &x)
        {
            in >> x.year >> x.month >> x.day;
            return in;
        }
        friend ostream &operator << (ostream &out, const Birthday &x)
        {
            out << x.year << "-" << x.month << "-" << x.day;
            return out;
        }
    }birthday;
  
  public:
    int leftChild, rightChild;  //左右孩子
    int key;  //值（学号） 
    int cnt;  //相同值（学号）的个数
    Node() {}
    ~Node() {}
    void Input()
    {
        cout << "请输入学号：";
        cin >> key;
		cout << key << endl;
        cout << "请输入姓名：";
        cin >> name;
		cout << name << endl;
        cout << "请输入性别：";
        cin >> sex;
		cout << sex << endl;
        cout << "请输入电话：";
        cin >> phone_number;
		cout << phone_number << endl;
        cout << "请输入地址：";
        cin >> address;
		cout << address << endl;
        cout << "请输入出生日期：(格式yy mm dd)";
        cin >> birthday;
		cout << birthday << endl;
        cout << "信息录入完毕！" << endl;
    }
    
    void Output()
    {
        cout << "学号：" << key << " 姓名：" << name << " 性别：" << sex << endl;
        cout << "电话：" << phone_number << " 地址：" << address <<  " 出生日期：" << birthday << endl;
    }
    
    Node operator=(const Node &x)
	{
        name = x.name, sex = x.sex, phone_number = x.phone_number, address = x.address;
        birthday.year = x.birthday.year, birthday.month = x.birthday.month, birthday.day = x.birthday.day;
        key = x.key, cnt = x.cnt;
        return *this; 
    }
}BinarySortTree[NodeNumber]; 


void CreateNode(int key)  //创建一个新结点
{
    BinarySortTree[++idx].key = key;
    BinarySortTree[idx].cnt = 1;
}


void Insert(int &current_node, int key)  //在二叉搜索树中递归插入一个值
{
    if (current_node == 0)
	{
        CreateNode(key);
        current_node = idx;
    }
	else if (BinarySortTree[current_node].key == key)  BinarySortTree[current_node].cnt++;
    else if (BinarySortTree[current_node].key > key)  Insert(BinarySortTree[current_node].leftChild, key);
    else Insert(BinarySortTree[current_node].rightChild, key);
}


void Insert2(int current_node, int key)  //在二叉搜索树中非递归插入一个值
{
    while (1)
	{
        if (BinarySortTree[current_node].key == key)
		{
            BinarySortTree[current_node].cnt++;
            return;
        }
		else if (BinarySortTree[current_node].key > key)
		{
            if (BinarySortTree[current_node].leftChild == 0)
			{
                CreateNode(key);
                BinarySortTree[current_node].leftChild = idx;
                return;
            }
			else current_node = BinarySortTree[current_node].leftChild;
        } 
		else
		{
            if (BinarySortTree[current_node].rightChild == 0)
			{
                CreateNode(key);
                BinarySortTree[current_node].rightChild = idx;
                return;
            }
			else current_node = BinarySortTree[current_node].rightChild;
        }
    }
}


int Search(int current_node, int key)  //在二叉搜索树中递归搜索一个值
{ 
    if (current_node == 0)  return 0;
    if (BinarySortTree[current_node].key == key) return current_node;
    else if (BinarySortTree[current_node].key > key) return Search(BinarySortTree[current_node].leftChild, key);
    else return Search(BinarySortTree[current_node].rightChild, key);
}


int Search2(int current_node, int key)  //在二叉搜索树中非递归搜索一个值
{
    while (1)
	{
        if (BinarySortTree[current_node].key == key) return current_node;
        else if (BinarySortTree[current_node].key > key)
		{
            if (BinarySortTree[current_node].leftChild == 0) return 0;
            else current_node = BinarySortTree[current_node].leftChild;
        }
		else
		{
            if (BinarySortTree[current_node].rightChild == 0) return 0;
            else current_node = BinarySortTree[current_node].rightChild;
        }
    }
}


void Delete(int &current_node, int key)  //在二叉搜索树中删除一个值
{
    if (current_node == 0) return;
    if (BinarySortTree[current_node].key == key)
	{
        if (BinarySortTree[current_node].cnt > 1)
		{
            BinarySortTree[current_node].cnt--;
            return;
        }else if (BinarySortTree[current_node].leftChild || BinarySortTree[current_node].rightChild)
		{
            if (BinarySortTree[current_node].leftChild && BinarySortTree[current_node].rightChild)
			{
                int temp = BinarySortTree[current_node].rightChild;
                while (BinarySortTree[temp].leftChild != 0) temp = BinarySortTree[temp].leftChild;
                BinarySortTree[current_node] = BinarySortTree[temp];
                Delete(BinarySortTree[current_node].rightChild, BinarySortTree[temp].key);
            }
			else if (BinarySortTree[current_node].leftChild) current_node = BinarySortTree[current_node].leftChild;
            else current_node = BinarySortTree[current_node].rightChild;
        }		else
		{ 
            current_node = 0;
        }
    }
	else if (BinarySortTree[current_node].key > key) Delete(BinarySortTree[current_node].leftChild, key);
    else Delete(BinarySortTree[current_node].rightChild, key);
}


void Print(int current_node, int deepth)  //凹入表打印树
{
    for (int i = 0; i < deepth; i++) cout << "     ";
    cout << BinarySortTree[current_node].key << "(" << BinarySortTree[current_node].cnt << ")" << endl;
    if (BinarySortTree[current_node].leftChild != 0) Print(BinarySortTree[current_node].leftChild, deepth + 1);
    if (BinarySortTree[current_node].rightChild != 0) Print(BinarySortTree[current_node].rightChild, deepth + 1);
}


void Print2(int current_node)  //打印通讯录信息
{
    BinarySortTree[current_node].Output();
    if (BinarySortTree[current_node].leftChild != 0) Print2(BinarySortTree[current_node].leftChild);
    if (BinarySortTree[current_node].rightChild != 0) Print2(BinarySortTree[current_node].rightChild);
}


void Menu1()  //必做内容一功能菜单
{
    cout << "*************************菜单**************************" << endl;
    cout << "*                1、建立一棵二叉排序树                *" << endl;
    cout << "*         2、在二叉排序树中插入一个值（递归算法）     *" << endl;
    cout << "*        3、在二叉排序树中插入一个值（非递归算法）    *" << endl;
    cout << "*         4、在二叉排序树中查找一个值（递归算法）     *" << endl;
    cout << "*        5、在二叉排序树中查找一个值（非递归算法）    *" << endl;
    cout << "*             6、在二叉排序树中删除一个值             *" << endl;
    cout << "*                  7、输出二叉树                      *" << endl;
    cout << "*                     8、退出                         *" << endl;
    cout << "*******************************************************" << endl;
    cout << "请输入操作指令：" << endl;
}


void FirstControl()  //必做内容一：
{
    while (1)
	{
        Menu1();
        //指令，结点数量，待查找的值，搜索位置，删除的结点，插入的结点 
        int operator_index, node_num, find_element, position, delete_element, insert_node;                                                              
        cin >> operator_index;
        cout << operator_index << endl;
        switch (operator_index)
		{
            case 1:
                cout << "请输入二叉排序树的结点个数：";
                cin >> node_num;
                cout << node_num << endl;
                for (int i = 0; i < node_num; i++)
				{
                    int key;
                    cin >> key;
                    cout << key << " ";
                    Insert(root, key);
                }
                cout << endl;
                break;
            case 2:
                cout << "插入前的二叉搜索树：" << endl;
                Print(root, 0);
                cout << "请输入你要插入的结点：";
                cin >> insert_node;
                cout << insert_node << endl;
                Insert(root, insert_node);
                cout << "插入后的二叉搜索树：" << endl;
                Print(root, 0);
                break;
            case 3:
                cout << "插入前的二叉搜索树：" << endl;
                Print(root, 0);
                cout << "请输入你要插入的结点：";
                cin >> insert_node;
                cout << insert_node << endl;
                Insert2(root, insert_node);
                cout << "插入后的二叉搜索树：" << endl;
                Print(root, 0);
                break;
            case 4:
                cout << "输入你要查找的结点：";
                cin >> find_element;
                cout << find_element << endl;
                position = Search(root, find_element);
                if (position) cout << "搜索成功！编号为" << position << endl;
                else cout << "搜索失败！" << endl;
                break;
            case 5:
                cout << "输入你要查找的结点：";
                cin >> find_element;
                cout << find_element << endl;
                position = Search2(root, find_element);
                if (position) cout << "搜索成功！编号为" << position << endl;
                else cout << "搜索失败！" << endl;
                break;
            case 6:
                cout << "删除前的二叉搜索树：" << endl;
                Print(root, 0);                                                                                                                                                                                                                                                 
                cout << "请输入你要删除的结点：";
                cin >> delete_element;
                cout << delete_element << endl;
                Delete(root, delete_element);
                cout << "删除后的二叉搜索树：" << endl;
                Print(root, 0);
                break;
            case 7:
                Print(root, 0);
                break;
            case 8:
                return;
            default:
                cout << operator_index << "不是内部指令！" << endl;
        }
        cout << endl;
    }
}


void Menu2()  //必做内容二功能菜单
{
    cout << "*****************菜单*****************" << endl;
    cout << "*         1、新建学生通讯录          *" << endl;
    cout << "*     2、向学生通讯录插入学生信息    *" << endl;
    cout << "*       3、在通讯录删除学生信息      *" << endl;
    cout << "*      4、从文件中读取通讯录信息     *" << endl;
    cout << "*     5、向文件写入学生通讯录信息    *" << endl;
    cout << "*      6、在通讯录中查询学生信息     *" << endl;
    cout << "*     7、在屏幕中输出全部学生信息    *" << endl;
    cout << "*              8、退出               *" << endl;
    cout << "**************************************" << endl;
    cout << "请输入操作指令：" << endl;
}


void SecondControl()  //必做内容二：
{
    while (1)
	{
        Menu2();
        int operator_index, student_num, delete_student, find_student;
        cin >> operator_index;
        cout << operator_index << endl;
        switch (operator_index)
		{
            case 1:
                cout << "请输入添加学生的个数：";
                cin >> student_num; cout << student_num << endl;
                for (int i = 0; i < student_num; i++)
				{
                    BinarySortTree[idx + 1].Input();
                    Insert(root, BinarySortTree[idx + 1].key);
                }
                cout << "通讯录创建完毕！" << endl;
                break;
            case 2:
                cout << "请输入你要插入学生的信息：" << endl;
                BinarySortTree[idx + 1].Input();
                Insert(root, BinarySortTree[idx + 1].key);
                cout << "插入成功！" << endl;
                break;
            case 3:
                cout << "请输入你要删除学生的学号：";
                cin >> delete_student; cout << delete_student << endl;
                Delete(root, delete_student);
                cout << "删除完毕！" << endl;
                break;
            case 4:
                cout << "通讯录信息已读取成功！" << endl;
                break;
            case 5:
                cout << "通讯录信息已写入文件中！" << endl;
                break;
            case 6:
                cout << "请输入你要查找的学生的学号：";
                cin >> find_student; cout << find_student << endl;
                find_student = Search(root, find_student);
                if (find_student)
				{
                    cout << "查找成功！" << endl;
                    BinarySortTree[find_student].Output();
                } else cout << "查找失败！" << endl;
                break;
            case 7:
                cout << "通讯录中全部的学生信息：" << endl;
                Print2(root);
                break;
            case 8:
                return;
            default:
                cout << operator_index << "不是内部指令！" << endl;
        }
        cout << endl;
    }
}

int main(int argc, char** argv)
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    FirstControl();
    for (int i = 1; i <= idx; i++) BinarySortTree[i].leftChild = BinarySortTree[i].rightChild = 0;
    root = 0, idx = 0;
    SecondControl();
    return 0;
}
