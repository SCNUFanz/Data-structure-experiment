#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <cstring>
#include <fstream> 
#include <algorithm> 
using namespace std;
const int NodeNumber = 100;  //������

int root, idx;  //����㣬���ָ��

class Node
{
  private:
    string sex, name, address, phone_number;  // �������Ա𡢵绰����ַ
    
    struct Birthday  //��������
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
    int leftChild, rightChild;  //���Һ���
    int key;  //ֵ��ѧ�ţ� 
    int cnt;  //��ֵͬ��ѧ�ţ��ĸ���
    Node() {}
    ~Node() {}
    void Input()
    {
        cout << "������ѧ�ţ�";
        cin >> key;
		cout << key << endl;
        cout << "������������";
        cin >> name;
		cout << name << endl;
        cout << "�������Ա�";
        cin >> sex;
		cout << sex << endl;
        cout << "������绰��";
        cin >> phone_number;
		cout << phone_number << endl;
        cout << "�������ַ��";
        cin >> address;
		cout << address << endl;
        cout << "������������ڣ�(��ʽyy mm dd)";
        cin >> birthday;
		cout << birthday << endl;
        cout << "��Ϣ¼����ϣ�" << endl;
    }
    
    void Output()
    {
        cout << "ѧ�ţ�" << key << " ������" << name << " �Ա�" << sex << endl;
        cout << "�绰��" << phone_number << " ��ַ��" << address <<  " �������ڣ�" << birthday << endl;
    }
    
    Node operator=(const Node &x)
	{
        name = x.name, sex = x.sex, phone_number = x.phone_number, address = x.address;
        birthday.year = x.birthday.year, birthday.month = x.birthday.month, birthday.day = x.birthday.day;
        key = x.key, cnt = x.cnt;
        return *this; 
    }
}BinarySortTree[NodeNumber]; 


void CreateNode(int key)  //����һ���½��
{
    BinarySortTree[++idx].key = key;
    BinarySortTree[idx].cnt = 1;
}


void Insert(int &current_node, int key)  //�ڶ����������еݹ����һ��ֵ
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


void Insert2(int current_node, int key)  //�ڶ����������зǵݹ����һ��ֵ
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


int Search(int current_node, int key)  //�ڶ����������еݹ�����һ��ֵ
{ 
    if (current_node == 0)  return 0;
    if (BinarySortTree[current_node].key == key) return current_node;
    else if (BinarySortTree[current_node].key > key) return Search(BinarySortTree[current_node].leftChild, key);
    else return Search(BinarySortTree[current_node].rightChild, key);
}


int Search2(int current_node, int key)  //�ڶ����������зǵݹ�����һ��ֵ
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


void Delete(int &current_node, int key)  //�ڶ�����������ɾ��һ��ֵ
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


void Print(int current_node, int deepth)  //������ӡ��
{
    for (int i = 0; i < deepth; i++) cout << "     ";
    cout << BinarySortTree[current_node].key << "(" << BinarySortTree[current_node].cnt << ")" << endl;
    if (BinarySortTree[current_node].leftChild != 0) Print(BinarySortTree[current_node].leftChild, deepth + 1);
    if (BinarySortTree[current_node].rightChild != 0) Print(BinarySortTree[current_node].rightChild, deepth + 1);
}


void Print2(int current_node)  //��ӡͨѶ¼��Ϣ
{
    BinarySortTree[current_node].Output();
    if (BinarySortTree[current_node].leftChild != 0) Print2(BinarySortTree[current_node].leftChild);
    if (BinarySortTree[current_node].rightChild != 0) Print2(BinarySortTree[current_node].rightChild);
}


void Menu1()  //��������һ���ܲ˵�
{
    cout << "*************************�˵�**************************" << endl;
    cout << "*                1������һ�ö���������                *" << endl;
    cout << "*         2���ڶ����������в���һ��ֵ���ݹ��㷨��     *" << endl;
    cout << "*        3���ڶ����������в���һ��ֵ���ǵݹ��㷨��    *" << endl;
    cout << "*         4���ڶ����������в���һ��ֵ���ݹ��㷨��     *" << endl;
    cout << "*        5���ڶ����������в���һ��ֵ���ǵݹ��㷨��    *" << endl;
    cout << "*             6���ڶ�����������ɾ��һ��ֵ             *" << endl;
    cout << "*                  7�����������                      *" << endl;
    cout << "*                     8���˳�                         *" << endl;
    cout << "*******************************************************" << endl;
    cout << "���������ָ�" << endl;
}


void FirstControl()  //��������һ��
{
    while (1)
	{
        Menu1();
        //ָ���������������ҵ�ֵ������λ�ã�ɾ���Ľ�㣬����Ľ�� 
        int operator_index, node_num, find_element, position, delete_element, insert_node;                                                              
        cin >> operator_index;
        cout << operator_index << endl;
        switch (operator_index)
		{
            case 1:
                cout << "����������������Ľ�������";
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
                cout << "����ǰ�Ķ�����������" << endl;
                Print(root, 0);
                cout << "��������Ҫ����Ľ�㣺";
                cin >> insert_node;
                cout << insert_node << endl;
                Insert(root, insert_node);
                cout << "�����Ķ�����������" << endl;
                Print(root, 0);
                break;
            case 3:
                cout << "����ǰ�Ķ�����������" << endl;
                Print(root, 0);
                cout << "��������Ҫ����Ľ�㣺";
                cin >> insert_node;
                cout << insert_node << endl;
                Insert2(root, insert_node);
                cout << "�����Ķ�����������" << endl;
                Print(root, 0);
                break;
            case 4:
                cout << "������Ҫ���ҵĽ�㣺";
                cin >> find_element;
                cout << find_element << endl;
                position = Search(root, find_element);
                if (position) cout << "�����ɹ������Ϊ" << position << endl;
                else cout << "����ʧ�ܣ�" << endl;
                break;
            case 5:
                cout << "������Ҫ���ҵĽ�㣺";
                cin >> find_element;
                cout << find_element << endl;
                position = Search2(root, find_element);
                if (position) cout << "�����ɹ������Ϊ" << position << endl;
                else cout << "����ʧ�ܣ�" << endl;
                break;
            case 6:
                cout << "ɾ��ǰ�Ķ�����������" << endl;
                Print(root, 0);                                                                                                                                                                                                                                                 
                cout << "��������Ҫɾ���Ľ�㣺";
                cin >> delete_element;
                cout << delete_element << endl;
                Delete(root, delete_element);
                cout << "ɾ����Ķ�����������" << endl;
                Print(root, 0);
                break;
            case 7:
                Print(root, 0);
                break;
            case 8:
                return;
            default:
                cout << operator_index << "�����ڲ�ָ�" << endl;
        }
        cout << endl;
    }
}


void Menu2()  //�������ݶ����ܲ˵�
{
    cout << "*****************�˵�*****************" << endl;
    cout << "*         1���½�ѧ��ͨѶ¼          *" << endl;
    cout << "*     2����ѧ��ͨѶ¼����ѧ����Ϣ    *" << endl;
    cout << "*       3����ͨѶ¼ɾ��ѧ����Ϣ      *" << endl;
    cout << "*      4�����ļ��ж�ȡͨѶ¼��Ϣ     *" << endl;
    cout << "*     5�����ļ�д��ѧ��ͨѶ¼��Ϣ    *" << endl;
    cout << "*      6����ͨѶ¼�в�ѯѧ����Ϣ     *" << endl;
    cout << "*     7������Ļ�����ȫ��ѧ����Ϣ    *" << endl;
    cout << "*              8���˳�               *" << endl;
    cout << "**************************************" << endl;
    cout << "���������ָ�" << endl;
}


void SecondControl()  //�������ݶ���
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
                cout << "���������ѧ���ĸ�����";
                cin >> student_num; cout << student_num << endl;
                for (int i = 0; i < student_num; i++)
				{
                    BinarySortTree[idx + 1].Input();
                    Insert(root, BinarySortTree[idx + 1].key);
                }
                cout << "ͨѶ¼������ϣ�" << endl;
                break;
            case 2:
                cout << "��������Ҫ����ѧ������Ϣ��" << endl;
                BinarySortTree[idx + 1].Input();
                Insert(root, BinarySortTree[idx + 1].key);
                cout << "����ɹ���" << endl;
                break;
            case 3:
                cout << "��������Ҫɾ��ѧ����ѧ�ţ�";
                cin >> delete_student; cout << delete_student << endl;
                Delete(root, delete_student);
                cout << "ɾ����ϣ�" << endl;
                break;
            case 4:
                cout << "ͨѶ¼��Ϣ�Ѷ�ȡ�ɹ���" << endl;
                break;
            case 5:
                cout << "ͨѶ¼��Ϣ��д���ļ��У�" << endl;
                break;
            case 6:
                cout << "��������Ҫ���ҵ�ѧ����ѧ�ţ�";
                cin >> find_student; cout << find_student << endl;
                find_student = Search(root, find_student);
                if (find_student)
				{
                    cout << "���ҳɹ���" << endl;
                    BinarySortTree[find_student].Output();
                } else cout << "����ʧ�ܣ�" << endl;
                break;
            case 7:
                cout << "ͨѶ¼��ȫ����ѧ����Ϣ��" << endl;
                Print2(root);
                break;
            case 8:
                return;
            default:
                cout << operator_index << "�����ڲ�ָ�" << endl;
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
