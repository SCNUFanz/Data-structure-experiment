#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

template <class T>
struct BinTreeNode
{
	T data;                //节点数据 
	int index;             //顺序存储二叉树的数组下标
	BinTreeNode<T> *leftChild, *rightChild;  //左、右节点指针 
	BinTreeNode(): leftChild(NULL), rightChild(NULL) {}
	BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL):
		data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree
{
	public:
		BinTreeNode<T>* root;        //指向根节点的指针
		
		
		BinaryTree():root(NULL) {}  //构造函数
		~BinaryTree()               //析构函数 
		{
			destory(root); 
		}
		bool IsEmpty()              //判二叉树空否 
		{
			return (root == NULL) ? true : false;
		}
		void CreateBinTree(int num);        //建立链式二叉树
		void destory(BinTreeNode<T> *subTree);    //删除当前节点的子树 
		int TreeHeight(BinTreeNode<T> *subTree);   //树的高度
		int LeavesNumber(BinTreeNode<T> *subTree); //叶节点数量 
		void preOrder(BinTreeNode<T> *subTree);   //递归前序遍历
		void preOrder2(BinTreeNode<T> *subTree);  //非递归前序遍历
		void inOrder(BinTreeNode<T> *subTree);    //递归中序遍历
		void inOrder2(BinTreeNode<T> *subTree);   //非递归中序遍历
		void postOrder(BinTreeNode<T> *subTree);  //递归后序遍历
		void postOrder2(BinTreeNode<T> *subTree); //非递归后序遍历
		void levelOrder(BinTreeNode<T> *subTree); //层次遍历
		int Level(BinTreeNode<T> *subTree);       //值x的层次
		bool Ancestors(BinTreeNode<T>* subTree, T x); //值x的所有祖先
		
};

template <class T>
void BinaryTree<T>::CreateBinTree(int num)  //建立链式二叉树
{
	T x;
	vector<T> Temp;
	Temp.push_back(T(0));
	for (int i = 0; i < num; i++)
	{
		cin >> x;
		Temp.push_back(x);
	}
	BinTreeNode<T>* t = new BinTreeNode<T>(Temp[1]);
    t->index = 1;
    root = t;
    queue<BinTreeNode<T>*> Q;
    Q.push(root);
    for (int i = 1; i <= num; i++)
	{
        if (Temp[i] != 0)
		{
            BinTreeNode<T>* cur = Q.front();
            Q.pop();
            BinTreeNode<T>* right = new BinTreeNode<T>();
            BinTreeNode<T>* left = new BinTreeNode<T>();
            int lc = i << 1, rc = i << 1 | 1;
            if (lc < num + 1 && Temp[lc] != 0)
			{
                left->data = Temp[lc];
                left->index = lc;
                cur->leftChild = left;
                Q.push(left);
            }
            if (rc < num + 1 && Temp[rc] != 0)
			{
                right->data = Temp[rc];
                right->index = rc;
                cur->rightChild = right;
                Q.push(right);
            }
        }
    }
    cout << "建立二叉树成功！" << endl;
}

template <class T>
int BinaryTree<T>::TreeHeight(BinTreeNode<T> *subTree)  //树的高度 
{
	if (subTree == NULL)
	{
		return 0;
	}
	int a = TreeHeight(subTree->leftChild);
	int b = TreeHeight(subTree->rightChild);
	return max(a, b) + 1;   //返回左和右子树高度中更高的那个 
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> *subTree)  //递归前序遍历 
{
	if (subTree == NULL)  return;
	cout << subTree->data << " ";
	preOrder(subTree->leftChild);
	preOrder(subTree->rightChild);
}

template <class T>
void BinaryTree<T>::preOrder2(BinTreeNode<T> *subTree)  //非递归前序遍历
{
	stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = subTree;
    S.push(p);
    while (S.size())
	{
        p = S.top();
        S.pop();
        cout << p->data << " ";
        if (p->rightChild != NULL)
		{
            S.push(p->rightChild);
        }
        if (p->leftChild != NULL)
		{
            S.push(p->leftChild);
        }
    }
} 

template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> *subTree)  //递归中序遍历 
{
	if (subTree == NULL)  return;
	inOrder(subTree->leftChild);
	cout << subTree->data << " ";
	inOrder(subTree->rightChild);
}

template <class T>
void BinaryTree<T>::inOrder2(BinTreeNode<T> *subTree)  //非递归中序遍历
{
	stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = subTree;
    do {
        while (p != NULL)
		{
            S.push(p);
            p = p->leftChild;
        }
        if (S.size())
		{
            p = S.top();
            S.pop();
            cout << p->data << " ";
            p = p->rightChild;
        }
    } while (p != NULL || S.size());
}

template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T> *subTree)  //递归后序遍历
{
	if (subTree == NULL)  return;
	postOrder(subTree->leftChild);
	postOrder(subTree->rightChild);
	cout << subTree->data << " ";

}

template <class T>
void BinaryTree<T>::postOrder2(BinTreeNode<T> *subTree)  //非递归后序遍历
{
	stack<pair<BinTreeNode<int>*, char> > S;
    pair<BinTreeNode<int>*, char> w;
    BinTreeNode<T>* p = subTree;
    do {
        while (p != NULL)
		{
            w.first = p;
            w.second = 'L';
            S.push(w);
            p = p->leftChild;
        }
        bool flag = true;
        while (flag && S.size())
		{
            w = S.top();
            S.pop();
            p = w.first;
            switch(w.second)
			{
                case 'L': 
                    w.second = 'R';
                    S.push(w);
                    flag = false;
                    p = p->rightChild;
                    break;
                case 'R':
                    cout << p->data << " ";
                    break;
            }
        }
    } while (S.size());
}

template <class T>
void BinaryTree<T>::destory(BinTreeNode<T> *subTree) //删除当前节点的子树 
{
	if (subTree != NULL)
	{
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;    //释放空间 
	}
}

template <class T>
int BinaryTree<T>::LeavesNumber(BinTreeNode<T> *subTree) //统计叶节点的数量 
{
	static int leafnum = 0;
    if (subTree == NULL)  return 0;
    if (subTree->leftChild == NULL && subTree->rightChild == NULL)
	{
		leafnum++;   //同时没有左、右节点的才是叶节点 
	}
    LeavesNumber(subTree->leftChild);
    LeavesNumber(subTree->rightChild);
    return leafnum;
}

template <class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T> *subTree) //层次遍历
{
	if (subTree == NULL)  return;
    queue<BinTreeNode<T>*> Q;
    Q.push(subTree);
    int level = 1;
    while (Q.size())
	{
        BinTreeNode<T>* cur = Q.front();
        Q.pop();
        int temp = log(cur->index) / log(2) + 1;
        if (temp != level)
		{
            cout << endl;
			level = temp;
        }
        cout << cur->data << " ";
        if (cur->leftChild != NULL)  Q.push(cur->leftChild);
        if (cur->rightChild != NULL)  Q.push(cur->rightChild);
    }
}

template <class T>
int BinaryTree<T>::Level(BinTreeNode<T> *subTree) //值x的层次
{
	T x;
	cin >> x;
	if (subTree == NULL) return 0;
    queue<BinTreeNode<T>*> Q;
    Q.push(subTree);
    int level = 1;
    while (Q.size())
	{
        BinTreeNode<T>* cur = Q.front();
        Q.pop();
        if (cur->data == x)
		{
            int tnum = log(cur->index) / log(2) + 1;
            return tnum;
        }
        if (cur->leftChild != NULL)  Q.push(cur->leftChild);
        if (cur->rightChild != NULL)  Q.push(cur->rightChild);
    }
    return 0;
}

template <class T>
bool BinaryTree<T>::Ancestors(BinTreeNode<T>* subTree, T x)  //值x的所有祖先 
{
    if (subTree == NULL)  return false;
    if (subTree->data == x)  return true;
    if (Ancestors(subTree->leftChild, x) || Ancestors(subTree->rightChild, x))
	{
        cout << subTree->data << " ";
        return true;
    }
    return false;
}



void Menu()    //菜单函数 
{
	int choice;
	BinaryTree<int> T;
	while (1)
	{
		cout << "*********************二叉树程序菜单*********************" << endl;
		cout << "**  1.建立二叉树    2.前序递归遍历   3.前序非递归遍历 **" << endl;
		cout << "**  4.中序递归遍历  5.中序非递归遍历  6.后序递归遍历  **" << endl;
		cout << "**  7.后序非递归遍历   8.树的高度     9.叶节点总数    **" << endl;
		cout << "**  10.值x的层次    11.值x的所有祖先  12.层次遍历     **" << endl;
		cout << "********************************************************" << endl;
		cout << "请选择操作：";
		cin >> choice; 
		if (choice == 1)
		{
			int num;
			cout << "请输入要建立的二叉树的节点个数：";
			cin >> num;
			if (num > 0)
			{
				cout << "请依次输入节点数据：";
				T.CreateBinTree(num);
			}	
		}
		else if (choice == 2)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的递归前序遍历顺序为：";
				T.preOrder(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 3)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的非递归前序遍历顺序为：";
				T.preOrder2(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 4)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的递归中序遍历顺序为：";
				T.inOrder(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 5)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的非递归中序遍历顺序为：";
				T.inOrder2(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 6)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的递归后序遍历顺序为：";
				T.postOrder(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 7)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的非递归后序遍历顺序为：";
				T.postOrder2(T.root);
				cout << endl;
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else if (choice == 8)
		{
			cout << "二叉树的高度为：" << T.TreeHeight(T.root) << endl;
		}
		else if (choice == 9)
		{
			cout << "二叉树的叶子总数为：" << T.LeavesNumber(T.root) << endl;
		}
		else if (choice == 10)
		{
			cout << "请输入要查找层次的节点的值：";
			int ans = T.Level(T.root);
			if (ans)
			{ 
				cout << "层次为：" << ans << endl;
			}
			else cout << "二叉树不存在此值！" << endl;
		}
		else if (choice == 11)
		{
			int tt;
			cout << "请输入要查找所有祖先的节点的值：";
			cin >> tt;
			cout << tt << "的所有祖先为：";
			T.Ancestors(T.root, tt);
			cout << endl;
		}
		else if (choice == 12)
		{
			if (!T.IsEmpty())
			{
				cout << "二叉树的层次遍历顺序为：";
				T.levelOrder(T.root);
			}
			else cout << "二叉树为空！！！" << endl;
		}
		else break;
		cout << endl << endl;
	}
}


int main(int argc, char** argv)
{
	Menu();    //菜单显示
	return 0;
}
