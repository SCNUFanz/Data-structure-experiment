#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int Maxsize = 10;
const int Maxsons = 100;

struct NameT
{
    char fname[20];  //��λ����
    char sname[20];  //�¼���λ���ƻ�����
};

typedef struct node
{
	char data[20];  //����ֵ����λ���ƻ�����
	struct node *sons[Maxsons]; //ָ���ӽ��
}TSonNode;          //�����������洢�ṹ�������


void Read(NameT R[], int &n)  //��abc.txt�ļ�����R������
{
    n = 0;
	FILE *fp;
    fp = fopen("abc.txt", "r");
    if(fp == NULL)
    {
        cout << "�ļ���ʧ�ܣ�����" << endl;
        return;
    }
    while (!feof(fp))                    //������ϵ��ļ�������(�ļ�����:���ط�0ֵ,�ļ�δ����,����0ֵ)
    {
        fscanf(fp, "%s", R[n].fname);    //��fname����
        fscanf(fp, "%s", R[n].sname);    //��sname����
        n++;
    }
    fclose(fp);  //�ر��ļ�
}

TSonNode *TreeCreate(char root[], NameT R[], int n) //������
{
    TSonNode *temp;
    int i = 0, j = 0;
    temp = (TSonNode *)malloc(sizeof(TSonNode));  //���������
    strcpy(temp->data, root);
    for(int k = 0; k < Maxsize; k++)    //�������ָ��������Ϊ��
    {
        temp->sons[k] = NULL;
    }
    while(i < n)
    {
        if(strcmp(R[i].fname, root) == 0)  //�ҵ�fnameΪroot�Ľڵ� 
        {
            temp->sons[j] = TreeCreate(R[i].sname, R, n); //�ݹ鴴������
            j++;
        }
        i++;
    }
    return temp;
}

void TreeDisplay(TSonNode *t) //����������洢�ṹ
{
    if(t != NULL)
    {
        printf("%s", t->data);
        if(t->sons[0] != NULL)                //t���������һ������
        {
            cout << "(";                      //���һ��������
            for(int i = 0; i < Maxsize; i++)
            {
                TreeDisplay(t->sons[i]);
                if(t->sons[i + 1] != NULL)    //�������һ������
                    cout << ",";              //���","
                else                          //���û����һ������
                    break;                    //�˳�ѭ��
            }
            cout << ")";                      //���һ��������
        }
    }
}

void TreeDestroy(TSonNode *t)  //������t
{
    if(t != NULL)
    {
        for(int i = 0; i < Maxsize; i++)
        {
            if(t->sons[i] != NULL)            //������
			{            
                TreeDestroy(t->sons[i]);
			}                                //��������
            else
			{                                //û������
                break;
			}                                //�˳�ѭ��
        }
        free(t);                             //�ͷŸ����
    }
}

TSonNode *find_node(TSonNode *t, char x[])  //��ֵΪx����ָ��
{
    int i;
    TSonNode *p;
    if(t == NULL)
        return NULL;
    else if(strcmp(t->data, x) == 0)        //�ҵ�ֵΪx�Ľ��
        return t;
    else
    {
        for(i = 0; i < Maxsize; i++)
        {
            if(t->sons[i] != NULL)
            {
                p = find_node(t->sons[i], x);
                if(p != NULL)
                    return p;
            }
        }
        return NULL;
    }
}

int Leaf_sum(TSonNode *t)   //������Ҷ�ӽ�����ֵ��
{
    int sum = 0;
    if(t == NULL)
	{
		return 0;
	}
    else
    {
        if(t->sons[0] == NULL)                    //tΪҶ�ӽ��
            return atoi(t->data);                 //�ַ�����ʽ������תΪ���� 
        else                                      //t��ΪҶ�ӽ��
        {
            for(int i = 0; i < Maxsize; i++)
            {
            	if(t->sons[i] != NULL)
            	{
            		sum += Leaf_sum(t->sons[i]);
				}
				else
				{
					break;
				}
			}
        }
        return sum;
    }
}

int Child_count(TSonNode *p)  //��p��ָ���ĺ��Ӹ���
{
    int i, sum;
	TSonNode *t;
	int num = 0;
    for(i = 0; i < Maxsize; i++)
    {
        if(p->sons[i] != NULL)
		{
			num++;
		}
        else
		{
			break;
		}      
    }
    return num;
}

int Son_num(TSonNode *t, char x[])  //��x��λ����һ����λ��
{
    TSonNode *p;
    p = find_node(t, x);
    if(p == NULL)
	{
		return 0;
	}
    else
	{
		return Child_count(p);
	}
}

int Leaf_count(TSonNode *t)  //������Ҷ�ӽ�����
{
    int num = 0;
    if(t == NULL)
	{
		return 0;
	}
    else
    {
        if(t->sons[0] == NULL)                  //tΪҶ�ӽ��
		{
			num++;
		}                            
        else                                    //t��ΪҶ�ӽ��
        {
            for(int i = 0; i < Maxsize; i++)
            {
                if(t->sons[i] != NULL)
				{
                	num += Leaf_count(t->sons[i]);
				}
                else
				{
					break;
				}
            }
        }
        return num;
    }
}

int Class_num(TSonNode *t, char x[])  //��x��λ�İ���
{
    TSonNode *p;
    p = find_node(t, x);
    if(p == NULL)
	{
		return 0;
	}
    else
	{
		return Leaf_count(p);
	} 
}

int Stu_num(TSonNode *t, char x[])  //��x��λ����ѧ������
{
    TSonNode *p;
    p = find_node(t, x);
    if(p == NULL)
    {
    	return 0;
	}
    else
	{
		return Leaf_sum(p);
	}
}


void Menu()  //�˵����� 
{
	int n;
	TSonNode *t;
    NameT R[Maxsons];
	while(true)
	{
		int choice;
		cout << "****************************************" << endl; 
		cout << "**********���Ļ�������ʵ��ϵͳ**********" << endl;
		cout << "*  1���� abc.txt �ļ������ݵ���������  *" << endl;
		cout << "*  2��������Ҵ��������ĺ������洢�ṹ *" << endl;
		cout << "*        3���������ű�ʾ�������       *" << endl;
		cout << "*        4��������ѧԺ��רҵ��       *" << endl;
		cout << "*         5��������ѧԺ�İ���        *" << endl;
		cout << "*         6�������ѧԺ��ѧ����        *" << endl;
		cout << "*             7����������              *" << endl;
		cout << "*             8���˳�ϵͳ              *" << endl;
		cout << "****************************************" << endl;
		cout << "��ѡ��";
		cin >> choice;
		if (choice == 1)
		{
			Read(R, n);
			if (n == 0)
			{
				cout << "��Ϊ�գ�" << endl; 
			}
			else cout << "��ȡ�ɹ���" << endl; 
		}
		else if (choice == 2)
		{
			t = TreeCreate(R[0].fname, R, n);
			cout << "�����ɹ���" << endl;
		}
		else if (choice == 3)
		{
			cout << "�����������Ϊ��";
			TreeDisplay(t);
			cout << endl;
		}
		else if (choice == 4)
		{
			cout << "�����ѧԺרҵ��Ϊ��" << Son_num(t, "�����ѧԺ") << endl;
		}
		else if (choice == 5)
		{
			cout << "�����ѧԺ����Ϊ��" << Class_num(t, "�����ѧԺ") << endl;
		}
		else if (choice == 6)
		{
			cout << "����ѧԺѧ����Ϊ��" << Stu_num(t, "����ѧԺ") << endl;
		}
		else if (choice == 7)
		{
			TreeDestroy(t);
			cout << "���ٳɹ���" << endl; 
		}
		else break;
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	Menu();  //�˵�
	return 0;
}
