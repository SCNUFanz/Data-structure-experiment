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
    char fname[20];  //单位名称
    char sname[20];  //下级单位名称或人数
};

typedef struct node
{
	char data[20];  //结点的值：单位名称或人数
	struct node *sons[Maxsons]; //指向孩子结点
}TSonNode;          //声明孩子链存储结构结点类型


void Read(NameT R[], int &n)  //读abc.txt文件存入R数组中
{
    n = 0;
	FILE *fp;
    fp = fopen("abc.txt", "r");
    if(fp == NULL)
    {
        cout << "文件打开失败！！！" << endl;
        return;
    }
    while (!feof(fp))                    //检测流上的文件结束符(文件结束:返回非0值,文件未结束,返回0值)
    {
        fscanf(fp, "%s", R[n].fname);    //读fname数据
        fscanf(fp, "%s", R[n].sname);    //读sname数据
        n++;
    }
    fclose(fp);  //关闭文件
}

TSonNode *TreeCreate(char root[], NameT R[], int n) //创建树
{
    TSonNode *temp;
    int i = 0, j = 0;
    temp = (TSonNode *)malloc(sizeof(TSonNode));  //创建根结点
    strcpy(temp->data, root);
    for(int k = 0; k < Maxsize; k++)    //结点所有指针域设置为空
    {
        temp->sons[k] = NULL;
    }
    while(i < n)
    {
        if(strcmp(R[i].fname, root) == 0)  //找到fname为root的节点 
        {
            temp->sons[j] = TreeCreate(R[i].sname, R, n); //递归创建子树
            j++;
        }
        i++;
    }
    return temp;
}

void TreeDisplay(TSonNode *t) //输出孩子链存储结构
{
    if(t != NULL)
    {
        printf("%s", t->data);
        if(t->sons[0] != NULL)                //t结点至少有一个孩子
        {
            cout << "(";                      //输出一个左括号
            for(int i = 0; i < Maxsize; i++)
            {
                TreeDisplay(t->sons[i]);
                if(t->sons[i + 1] != NULL)    //如果有下一个孩子
                    cout << ",";              //输出","
                else                          //如果没有下一个孩子
                    break;                    //退出循环
            }
            cout << ")";                      //输出一个右括号
        }
    }
}

void TreeDestroy(TSonNode *t)  //销毁树t
{
    if(t != NULL)
    {
        for(int i = 0; i < Maxsize; i++)
        {
            if(t->sons[i] != NULL)            //有子树
			{            
                TreeDestroy(t->sons[i]);
			}                                //销毁子树
            else
			{                                //没有子树
                break;
			}                                //退出循环
        }
        free(t);                             //释放根结点
    }
}

TSonNode *find_node(TSonNode *t, char x[])  //求值为x结点的指针
{
    int i;
    TSonNode *p;
    if(t == NULL)
        return NULL;
    else if(strcmp(t->data, x) == 0)        //找到值为x的结点
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

int Leaf_sum(TSonNode *t)   //求树中叶子结点的数值和
{
    int sum = 0;
    if(t == NULL)
	{
		return 0;
	}
    else
    {
        if(t->sons[0] == NULL)                    //t为叶子结点
            return atoi(t->data);                 //字符串形式的数字转为整形 
        else                                      //t不为叶子结点
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

int Child_count(TSonNode *p)  //求p所指结点的孩子个数
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

int Son_num(TSonNode *t, char x[])  //求x单位的下一级单位数
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

int Leaf_count(TSonNode *t)  //求树中叶子结点个数
{
    int num = 0;
    if(t == NULL)
	{
		return 0;
	}
    else
    {
        if(t->sons[0] == NULL)                  //t为叶子结点
		{
			num++;
		}                            
        else                                    //t不为叶子结点
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

int Class_num(TSonNode *t, char x[])  //求x单位的班数
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

int Stu_num(TSonNode *t, char x[])  //求x单位的总学生人数
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


void Menu()  //菜单函数 
{
	int n;
	TSonNode *t;
    NameT R[Maxsons];
	while(true)
	{
		int choice;
		cout << "****************************************" << endl; 
		cout << "**********树的基本操作实现系统**********" << endl;
		cout << "*  1、从 abc.txt 文件读数据到Ｒ数组中  *" << endl;
		cout << "*  2、由数组Ｒ创建树ｔ的孩子链存储结构 *" << endl;
		cout << "*        3、采用括号表示输出树ｔ       *" << endl;
		cout << "*        4、求计算机学院的专业数       *" << endl;
		cout << "*         5、求计算机学院的班数        *" << endl;
		cout << "*         6、求电信学院的学生数        *" << endl;
		cout << "*             7、求销毁树              *" << endl;
		cout << "*             8、退出系统              *" << endl;
		cout << "****************************************" << endl;
		cout << "请选择：";
		cin >> choice;
		if (choice == 1)
		{
			Read(R, n);
			if (n == 0)
			{
				cout << "树为空！" << endl; 
			}
			else cout << "读取成功！" << endl; 
		}
		else if (choice == 2)
		{
			t = TreeCreate(R[0].fname, R, n);
			cout << "创建成功！" << endl;
		}
		else if (choice == 3)
		{
			cout << "树的括号输出为：";
			TreeDisplay(t);
			cout << endl;
		}
		else if (choice == 4)
		{
			cout << "计算机学院专业数为：" << Son_num(t, "计算机学院") << endl;
		}
		else if (choice == 5)
		{
			cout << "计算机学院班数为：" << Class_num(t, "计算机学院") << endl;
		}
		else if (choice == 6)
		{
			cout << "电信学院学生数为：" << Stu_num(t, "电信学院") << endl;
		}
		else if (choice == 7)
		{
			TreeDestroy(t);
			cout << "销毁成功！" << endl; 
		}
		else break;
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	Menu();  //菜单
	return 0;
}
