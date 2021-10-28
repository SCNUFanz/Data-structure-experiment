#include <iostream>
#include <list> 
#include <cmath> 
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
static const int MAX = 100;
static const int INFTY = (1 << 21);
static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;


int n;

/***�ڽӱ�***/
bool visit[MAX];  //�궨�����Ƿ񱻷��ʹ� 
vector<int> G[MAX];  //�ڽӱ�洢ͼ 
int nt[MAX], color[MAX];
list<int> out;
int indeg[MAX];
bool flag[MAX];

/***�ڽӾ���***/
int M[MAX][MAX];  //�ڽӾ���洢ͼ 


int next(int u)
{
	if (nt[u] < G[u].size())
	{
		nt[u]++;
		return G[u][nt[u] - 1];	
	}
	return -1;
}

void dfs_visit(int r)
{
	for (int i = 1; i <= n; i++)
	{
		nt[i] = 0;
		visit[i] = false;
	}
	
	stack<int> S;
	S.push(r);
	color[r] = GRAY;
	
	while(!S.empty())  //��ջ��Ϊ�յ�ʱ�� 
	{
		int u = S.top();
		int v = next(u);  //��һ���붥��u���ڵĵ� 
		if (visit[u] == false)
		{
			cout << u << " ";
			visit[u] = true;
		}
		if (v != -1)  //���û���붥��u���ڵĵ����� 
		{
			if (color[v] == WHITE)
			{
				color[v] = GRAY;
				S.push(v);
			}
		}
		else
		{
			S.pop();
			color[u] = BLACK;
		}
	}
}

void dfs()
{
	for (int i = 1; i <= n; i++)  //��ʼ�� 
	{
		color[i] = WHITE;
	}
	
	cout << "ͼ��������ȱ�����˳��Ϊ��"; 
	for (int u = 1; u <= n; u++)  //�������δ����Ķ�������ȱ����˵� 
	{
		if (color[u] == WHITE)  dfs_visit(u);
	}
	cout << endl;
}

void bfs()
{
	for (int i = 1; i <= n; i++)  //��ʼ�� 
	{
		nt[i] = 0;
		visit[i] = false;
		color[i] == WHITE;
	}
	
	queue<int> q;
	q.push(1);
	visit[1] = true;
	
	cout << "ͼ�Ĺ�����ȱ�����˳��Ϊ��";
	
	while(!q.empty())
	{
		int u = q.front();  //ȡ����ͷ�Ķ��� 
		cout << u << " ";
		q.pop();  //ɾ����ͷ 
		for (int i = 0; i < G[u].size(); i++)
		{
			if (!visit[G[u][i]])  //�����˵����ڵĵ���û�����ʹ����������� 
			{
				visit[G[u][i]] = true;
				q.push(G[u][i]);
			}
		}
	}
}

int prim()  //prim��С������ 
{
	int u, minv;
	int d[MAX], p[MAX];
	for (int i = 1; i <= n; i++)
	{
		d[i] = INFTY;
		p[i] = -1;
		color[i] = WHITE;
	}
	d[1] = 0;
	while (true)
	{
		minv = INFTY;
		u = -1;
		for (int i = 1; i <= n; i++)
		{
			if (minv > d[i] && color[i] != BLACK)
			{
				u = i;
				minv = d[i];
			}
		}
		if (u == -1)  break;
		color[u] = BLACK;
		for (int v = 1; v <= n; v++)
		{
			if (color[v] != BLACK && M[u][v] != INFTY)
			{
				if (d[v] > M[u][v])
				{
					d[v] = M[u][v];
					p[v] = u;
					color[v] = GRAY;
				}
			}
		}
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (p[i] != -1)
		{
			sum += M[i][p[i]];
		}
	}
	return sum;
}

void bfs2(int s)
{
    queue<int> q;
    q.push(s);

    while (!q.empty()) 
	{
        int u = q.front(); q.pop();
        out.push_back(u);
        for (int i = 0; i < G[u].size(); i++) 
		{
            int v = G[u][i];
            indeg[v]--;
            if (indeg[v] == 0 && flag[v] == 0) 
			{
                flag[v] = true;
                q.push(v);
            }
        }
    }
}

void tsort()  //�������� 
{
    for (int i = 1; i <= n; i++) 
	{
        indeg[i] = 0;
        flag[i] = false;
    }

    for (int u = 1; u <= n; u++) 
	{
        for (int i = 0; i < G[u].size(); i++) 
		{
            int v = G[u][i];
            indeg[v]++;
        }
    }
 	
	for (int u = 1; u <= n; u++) 
	{
        if (indeg[u] == 0 && flag[u] == 0)
            bfs2(u);
    }
    
    cout << "���������˳��Ϊ��"; 

    for (list<int>::iterator it = out.begin(); it != out.end(); it++)
	{
		cout << *it << " ";
	}
    cout << endl;
}

void dijkstra(int s)
{
	int minv;
	int d[MAX]; 
	for (int i = 1; i <= n; i++)
	{
		d[i] = INFTY;
		color[i] = WHITE;	
	}
	d[s] = 0;
	color[s] = GRAY;
	while (1)
	{
		minv = INFTY;
		int u = -1;
		for (int i = 1; i <= n; i++)
		{
			if (color[i] != BLACK && minv > d[i])
			{
				u = i;
				minv = d[i];
			}
		}
		if (u == -1)  break;
		color[u] = BLACK;
		for (int v = 1; v <= n; v++)
		{
			if (color[v] != BLACK && M[u][v] != INFTY)
			{
				if (d[v] > d[u] + M[u][v])
				{
					d[v] = d[u] + M[u][v];
					color[v] = GRAY;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "��" << s << "����" << i << "�ĵ�Դ���·��Ϊ��" << (d[i] == INFTY ? -1 : d[i])  << endl;
	}
}

void Menu()  //�˵����� 
{
	while(1)
	{
		cout << "*****************************" << endl;
		cout << "********ͼ�Ļ�������*********" << endl;
		cout << "*     1������ͼ���ڽӱ�     *" << endl;
		cout << "*    2������ͼ���ڽӾ���    *" << endl;
		cout << "*    3��ͼ��������ȱ���    *" << endl;
		cout << "*    4��ͼ�Ĺ�����ȱ���    *" << endl;
		cout << "*      5����С������        *" << endl;
		cout << "*       6����������         *" << endl;
		cout << "*     7����Դ���·��       *" << endl;
		cout << "*      8���˳�������        *" << endl;
		cout << "*****************************" << endl;
		cout << "������Ҫ������ѡ�";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			int u, k, v;
			cout << "������ͼ�Ķ��������"; 
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "�����붥��Ͷ���Ķȣ�"; 
				cin >> u >> k;
				if (k != 0)
				{
					cout << "�����������붥��" << u << "�����Ķ��㣺";
					for (int j = 0; j < k; j++)
					{
						cin >> v;
						G[u].push_back(v);
					}
				}
			}
			cout << "�ڽӱ�ͼ�ɹ�������" << endl;
		}
		else if (choice == 2)
		{
			cout << "������ͼ�Ķ��������"; 
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				cout << "�������" << i << "��������ľ���(�߲����ڼ�Ϊ-1)��"; 
				for (int j = 1; j <= n; j++)
				{
					int e;
					cin >> e;
					M[i][j] = (e == -1) ? INFTY : e;
				}
			}
			cout << "�ڽӾ���ͼ�ɹ�������" << endl;
		}
		else if (choice == 3)
		{
			dfs();
		}
		else if (choice == 4)
		{
			bfs();
		}
		else if (choice == 5)
		{
			cout << "ʹ��prim�㷨��ĵ���С������Ϊ��" << prim() << endl; 
		}
		else if (choice == 6)
		{
			tsort();
		}
		else if (choice == 7)
		{
			cout << "������ͼ�Ķ��������";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					M[i][j] = INFTY;
				}
			}
			int k, c, u, v;
			for (int i = 0; i < n; i++)
			{
				cout << "�����붥��Ͷ���Ķȣ�"; 
				cin >> u >> k;
				for (int j = 0; j < k; j++)
				{
					
					cout << "�����������붥��" << u << "�����Ķ���ͱߵ�Ȩֵ��";
					cin >> v >> c;
					M[u][v] = c;
				}
			}
			dijkstra(1);
			cout << endl; 
		}
		else if (choice == 8)
		{
			ofstream fop("TextFile.txt",ios::out|ios::binary|ios::trunc);  //���� 
 			fop << "Graph!";
 			fop.close();
 			cout << "�Ѵ浽�ļ�TextFile.txt�У�" << endl;
 			break;
		}
		cout << endl;
	}
}


int main(int argc, char** argv)
{
	Menu();  //�˵����� 
	return 0;
}

//�ڽӱ��������  6 1 2 2 3 2 2 3 4 3 1 5 4 1 6 5 1 6 6 0
//�ڽӾ���������� 5 -1 2 3 1 -1 2 -1 -1 4 -1 3 -1 -1 1 1 1 4 1 -1 3 -1 -1 1 3 -1
//��Դ���·���������� 5 1 3 3 3 4 1 2 2 2 2 1 2 4 4 3 3 1 3 4 1 5 1 4 4 3 1 1 1 2 4 5 3 5 2 3 1 4 3

