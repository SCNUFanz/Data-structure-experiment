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
	T data;                //�ڵ����� 
	int index;             //˳��洢�������������±�
	BinTreeNode<T> *leftChild, *rightChild;  //���ҽڵ�ָ�� 
	BinTreeNode(): leftChild(NULL), rightChild(NULL) {}
	BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL):
		data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree
{
	public:
		BinTreeNode<T>* root;        //ָ����ڵ��ָ��
		
		
		BinaryTree():root(NULL) {}  //���캯��
		~BinaryTree()               //�������� 
		{
			destory(root); 
		}
		bool IsEmpty()              //�ж������շ� 
		{
			return (root == NULL) ? true : false;
		}
		void CreateBinTree(int num);        //������ʽ������
		void destory(BinTreeNode<T> *subTree);    //ɾ����ǰ�ڵ������ 
		int TreeHeight(BinTreeNode<T> *subTree);   //���ĸ߶�
		int LeavesNumber(BinTreeNode<T> *subTree); //Ҷ�ڵ����� 
		void preOrder(BinTreeNode<T> *subTree);   //�ݹ�ǰ�����
		void preOrder2(BinTreeNode<T> *subTree);  //�ǵݹ�ǰ�����
		void inOrder(BinTreeNode<T> *subTree);    //�ݹ��������
		void inOrder2(BinTreeNode<T> *subTree);   //�ǵݹ��������
		void postOrder(BinTreeNode<T> *subTree);  //�ݹ�������
		void postOrder2(BinTreeNode<T> *subTree); //�ǵݹ�������
		void levelOrder(BinTreeNode<T> *subTree); //��α���
		int Level(BinTreeNode<T> *subTree);       //ֵx�Ĳ��
		bool Ancestors(BinTreeNode<T>* subTree, T x); //ֵx����������
		
};

template <class T>
void BinaryTree<T>::CreateBinTree(int num)  //������ʽ������
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
    cout << "�����������ɹ���" << endl;
}

template <class T>
int BinaryTree<T>::TreeHeight(BinTreeNode<T> *subTree)  //���ĸ߶� 
{
	if (subTree == NULL)
	{
		return 0;
	}
	int a = TreeHeight(subTree->leftChild);
	int b = TreeHeight(subTree->rightChild);
	return max(a, b) + 1;   //��������������߶��и��ߵ��Ǹ� 
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> *subTree)  //�ݹ�ǰ����� 
{
	if (subTree == NULL)  return;
	cout << subTree->data << " ";
	preOrder(subTree->leftChild);
	preOrder(subTree->rightChild);
}

template <class T>
void BinaryTree<T>::preOrder2(BinTreeNode<T> *subTree)  //�ǵݹ�ǰ�����
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
void BinaryTree<T>::inOrder(BinTreeNode<T> *subTree)  //�ݹ�������� 
{
	if (subTree == NULL)  return;
	inOrder(subTree->leftChild);
	cout << subTree->data << " ";
	inOrder(subTree->rightChild);
}

template <class T>
void BinaryTree<T>::inOrder2(BinTreeNode<T> *subTree)  //�ǵݹ��������
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
void BinaryTree<T>::postOrder(BinTreeNode<T> *subTree)  //�ݹ�������
{
	if (subTree == NULL)  return;
	postOrder(subTree->leftChild);
	postOrder(subTree->rightChild);
	cout << subTree->data << " ";

}

template <class T>
void BinaryTree<T>::postOrder2(BinTreeNode<T> *subTree)  //�ǵݹ�������
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
void BinaryTree<T>::destory(BinTreeNode<T> *subTree) //ɾ����ǰ�ڵ������ 
{
	if (subTree != NULL)
	{
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;    //�ͷſռ� 
	}
}

template <class T>
int BinaryTree<T>::LeavesNumber(BinTreeNode<T> *subTree) //ͳ��Ҷ�ڵ������ 
{
	static int leafnum = 0;
    if (subTree == NULL)  return 0;
    if (subTree->leftChild == NULL && subTree->rightChild == NULL)
	{
		leafnum++;   //ͬʱû�����ҽڵ�Ĳ���Ҷ�ڵ� 
	}
    LeavesNumber(subTree->leftChild);
    LeavesNumber(subTree->rightChild);
    return leafnum;
}

template <class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T> *subTree) //��α���
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
int BinaryTree<T>::Level(BinTreeNode<T> *subTree) //ֵx�Ĳ��
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
bool BinaryTree<T>::Ancestors(BinTreeNode<T>* subTree, T x)  //ֵx���������� 
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



void Menu()    //�˵����� 
{
	int choice;
	BinaryTree<int> T;
	while (1)
	{
		cout << "*********************����������˵�*********************" << endl;
		cout << "**  1.����������    2.ǰ��ݹ����   3.ǰ��ǵݹ���� **" << endl;
		cout << "**  4.����ݹ����  5.����ǵݹ����  6.����ݹ����  **" << endl;
		cout << "**  7.����ǵݹ����   8.���ĸ߶�     9.Ҷ�ڵ�����    **" << endl;
		cout << "**  10.ֵx�Ĳ��    11.ֵx����������  12.��α���     **" << endl;
		cout << "********************************************************" << endl;
		cout << "��ѡ�������";
		cin >> choice; 
		if (choice == 1)
		{
			int num;
			cout << "������Ҫ�����Ķ������Ľڵ������";
			cin >> num;
			if (num > 0)
			{
				cout << "����������ڵ����ݣ�";
				T.CreateBinTree(num);
			}	
		}
		else if (choice == 2)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ĵݹ�ǰ�����˳��Ϊ��";
				T.preOrder(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 3)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ķǵݹ�ǰ�����˳��Ϊ��";
				T.preOrder2(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 4)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ĵݹ��������˳��Ϊ��";
				T.inOrder(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 5)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ķǵݹ��������˳��Ϊ��";
				T.inOrder2(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 6)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ĵݹ�������˳��Ϊ��";
				T.postOrder(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 7)
		{
			if (!T.IsEmpty())
			{
				cout << "�������ķǵݹ�������˳��Ϊ��";
				T.postOrder2(T.root);
				cout << endl;
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else if (choice == 8)
		{
			cout << "�������ĸ߶�Ϊ��" << T.TreeHeight(T.root) << endl;
		}
		else if (choice == 9)
		{
			cout << "��������Ҷ������Ϊ��" << T.LeavesNumber(T.root) << endl;
		}
		else if (choice == 10)
		{
			cout << "������Ҫ���Ҳ�εĽڵ��ֵ��";
			int ans = T.Level(T.root);
			if (ans)
			{ 
				cout << "���Ϊ��" << ans << endl;
			}
			else cout << "�����������ڴ�ֵ��" << endl;
		}
		else if (choice == 11)
		{
			int tt;
			cout << "������Ҫ�����������ȵĽڵ��ֵ��";
			cin >> tt;
			cout << tt << "����������Ϊ��";
			T.Ancestors(T.root, tt);
			cout << endl;
		}
		else if (choice == 12)
		{
			if (!T.IsEmpty())
			{
				cout << "�������Ĳ�α���˳��Ϊ��";
				T.levelOrder(T.root);
			}
			else cout << "������Ϊ�գ�����" << endl;
		}
		else break;
		cout << endl << endl;
	}
}


int main(int argc, char** argv)
{
	Menu();    //�˵���ʾ
	return 0;
}
