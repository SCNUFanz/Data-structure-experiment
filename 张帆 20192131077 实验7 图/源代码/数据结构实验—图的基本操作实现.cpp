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

/***邻接表***/
bool visit[MAX];  //标定顶点是否被访问过 
vector<int> G[MAX];  //邻接表存储图 
int nt[MAX], color[MAX];
list<int> out;
int indeg[MAX];
bool flag[MAX];

/***邻接矩阵***/
int M[MAX][MAX];  //邻接矩阵存储图 


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
	
	while(!S.empty())  //当栈不为空的时候 
	{
		int u = S.top();
		int v = next(u);  //下一个与顶点u相邻的点 
		if (visit[u] == false)
		{
			cout << u << " ";
			visit[u] = true;
		}
		if (v != -1)  //如果没有与顶点u相邻的点的情况 
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
	for (int i = 1; i <= n; i++)  //初始化 
	{
		color[i] = WHITE;
	}
	
	cout << "图的深度优先遍历的顺序为："; 
	for (int u = 1; u <= n; u++)  //如果有尚未到达的顶点则深度遍历此点 
	{
		if (color[u] == WHITE)  dfs_visit(u);
	}
	cout << endl;
}

void bfs()
{
	for (int i = 1; i <= n; i++)  //初始化 
	{
		nt[i] = 0;
		visit[i] = false;
		color[i] == WHITE;
	}
	
	queue<int> q;
	q.push(1);
	visit[1] = true;
	
	cout << "图的广度优先遍历的顺序为：";
	
	while(!q.empty())
	{
		int u = q.front();  //取出队头的顶点 
		cout << u << " ";
		q.pop();  //删除队头 
		for (int i = 0; i < G[u].size(); i++)
		{
			if (!visit[G[u][i]])  //如果与此点相邻的点有没被访问过的则加入队列 
			{
				visit[G[u][i]] = true;
				q.push(G[u][i]);
			}
		}
	}
}

int prim()  //prim最小生成树 
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

void tsort()  //拓扑排序 
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
    
    cout << "拓扑排序的顺序为："; 

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
		cout << "点" << s << "到点" << i << "的单源最短路径为：" << (d[i] == INFTY ? -1 : d[i])  << endl;
	}
}

void Menu()  //菜单函数 
{
	while(1)
	{
		cout << "*****************************" << endl;
		cout << "********图的基本操作*********" << endl;
		cout << "*     1、建立图的邻接表     *" << endl;
		cout << "*    2、建立图的邻接矩阵    *" << endl;
		cout << "*    3、图的深度优先遍历    *" << endl;
		cout << "*    4、图的广度优先遍历    *" << endl;
		cout << "*      5、最小生成树        *" << endl;
		cout << "*       6、拓扑排序         *" << endl;
		cout << "*     7、单源最短路径       *" << endl;
		cout << "*      8、退出并保存        *" << endl;
		cout << "*****************************" << endl;
		cout << "请输入要操作的选项：";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			int u, k, v;
			cout << "请输入图的顶点个数："; 
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "请输入顶点和顶点的度："; 
				cin >> u >> k;
				if (k != 0)
				{
					cout << "请依次输入与顶点" << u << "相连的顶点：";
					for (int j = 0; j < k; j++)
					{
						cin >> v;
						G[u].push_back(v);
					}
				}
			}
			cout << "邻接表建图成功！！！" << endl;
		}
		else if (choice == 2)
		{
			cout << "请输入图的顶点个数："; 
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				cout << "请输入点" << i << "到各顶点的距离(边不存在记为-1)："; 
				for (int j = 1; j <= n; j++)
				{
					int e;
					cin >> e;
					M[i][j] = (e == -1) ? INFTY : e;
				}
			}
			cout << "邻接矩阵建图成功！！！" << endl;
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
			cout << "使用prim算法求的的最小生成树为：" << prim() << endl; 
		}
		else if (choice == 6)
		{
			tsort();
		}
		else if (choice == 7)
		{
			cout << "请输入图的顶点个数：";
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
				cout << "请输入顶点和顶点的度："; 
				cin >> u >> k;
				for (int j = 0; j < k; j++)
				{
					
					cout << "请依次输入与顶点" << u << "相连的顶点和边的权值：";
					cin >> v >> c;
					M[u][v] = c;
				}
			}
			dijkstra(1);
			cout << endl; 
		}
		else if (choice == 8)
		{
			ofstream fop("TextFile.txt",ios::out|ios::binary|ios::trunc);  //保存 
 			fop << "Graph!";
 			fop.close();
 			cout << "已存到文件TextFile.txt中！" << endl;
 			break;
		}
		cout << endl;
	}
}


int main(int argc, char** argv)
{
	Menu();  //菜单函数 
	return 0;
}

//邻接表测试样例  6 1 2 2 3 2 2 3 4 3 1 5 4 1 6 5 1 6 6 0
//邻接矩阵测试样例 5 -1 2 3 1 -1 2 -1 -1 4 -1 3 -1 -1 1 1 1 4 1 -1 3 -1 -1 1 3 -1
//单源最短路径测试样例 5 1 3 3 3 4 1 2 2 2 2 1 2 4 4 3 3 1 3 4 1 5 1 4 4 3 1 1 1 2 4 5 3 5 2 3 1 4 3

