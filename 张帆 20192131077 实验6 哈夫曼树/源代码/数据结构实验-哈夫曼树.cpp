#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct HuffmanNode   //定义哈夫曼节点 
{
	int weight;      //权值 
	int parent;      //存放父节点位置 
	int LeftChild;   //存放左子节点位置 
	int RightChild;  //存放右子节点位置 
};

class HuffmanTree    //定义哈夫曼树类 
{
	private:
		char *Info;         //字符信息 
		int LeafNum;        //叶节点数目 
		HuffmanNode* Node;  //哈夫曼节点 
		
	public:
		HuffmanTree();        //构造函数
 		~HuffmanTree();       //析构函数
 		void Initialization(int WeightNum);   //初始化函数：根据WeightNum个权值建立一棵哈夫曼树
		void Encoder();       //编码函数：利用构造好的哈夫曼树对字符进行编码
 		void Decoder();       //译码函数：对二进制串进行译码
 		void Print();         //打印文件函数：把已保存好的编码文件显示在屏幕
 		void TreePrinting();  //打印哈夫曼树函数：将已在内存中的哈夫曼树以直观的方式显示在终端上	
};

HuffmanTree::HuffmanTree()  //构造函数 
{
 	Node = NULL;  //将树结点初始化为空
 	Info = NULL;  //将字符数组初始化为空
 	LeafNum = 0;  //将叶子数初始化为0
}

HuffmanTree::~HuffmanTree()  //析构函数
{
	delete[] Info;
	delete[] Node;
}

//  函数功能：从终端读入字符集大小n，以及n个字符和n个权值,
//            建立哈夫曼树,并将它存放在文件hfmTree中.
void HuffmanTree::Initialization(int WeightNum)  //初始化函数
{
	
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*字符集*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*字符集对应的权值*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNum权值对应的哈夫曼树中的结点总数为2*WeightNum-1个
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "请输入第" << i + 1 << "个字符值：";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "请输入该字符的权值或频度：";
  		//cin >> Node[i].weight;    //输入权值
  		Node[i].parent = -1;      //为根结点
  		Node[i].LeftChild = -1;      //无左孩子
  		Node[i].RightChild = -1;      //无右孩子
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //表示需做WeightNum-1次合并
 	{
  		pos1 = -1;          //存放当前最小值的所在单元编号
  		pos2 = -1;          //存放当前次小值的所在单元编号
  		max1 = 32767;       //存放当前找到的最小值
  		max2 = 32767;       //存放当前找到的次小值 
		for(j = 0; j < i; j++)   //在未使用节点中选出权值最小的两个
		{      
   			if(Node[j].parent == -1)  //是否为根结点
			{         
    			if(Node[j].weight < max1)   //是否比最小值要小
    			{
     				max2 = max1;            //原最小值变为次小值
     				max1 = Node[j].weight;  //存放最小值
     				pos2 = pos1;            //修改次小值所在单元编号
     				pos1 = j;               //修改最小值所在单元编号
    			}
    			else if(Node[j].weight < max2)  //比原最小值大但比原次小值要小
     			{
      				max2 = Node[j].weight;  //存放次小值
      				pos2 = j;               //修改次小值所在的单元编号
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //修改父亲位置
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //修改儿子位置
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //表示新结点应该是根结点
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
 	LeafNum = WeightNum;
 	
	char ch;
 	cout << "是否要替换原来文件(Y/N):";
 	cin >> ch;
 	if(ch == 'Y')
 	{
 		ofstream fop;   //以二进制方式打开hfmTree.dat文件，并当重新运行时覆盖原文件
 		fop.open("hfmTree.txt", ios::out|ios::binary|ios::trunc);
 		if(fop.fail())  //文件打开失败
		{                    
  			cout << "文件打开失败！" << endl;
  		}
  		//fop << WeightNum;
 		fop.write((char*)&WeightNum, sizeof(WeightNum));  //写入WeightNum
 		for(i = 0; i < WeightNum; i++)           //把各字符信息写入文件
 		{
  			fop.write((char*)&Info[i], sizeof(Info[i]));
  			flush(cout);
 		}
 		for(i = 0; i < 2 * WeightNum - 1; i++)  //把各个节点内容写入文件
 		{
  			fop.write((char*)&Node[i], sizeof(Node[i]));
  			flush(cout);
 		}
 		fop.close();            //关闭文件
 	}
 	cout << "哈夫曼树已构造完成!" << endl << endl;
}


//  函数功能：利用已建立好的哈夫曼树（如不在内存，则从文件hfmTree中读入），
//            对文件ToBeTran中的正文进行编码,然后将结果代码存(传输)到文件CodeFile中.
void HuffmanTree::Encoder()  //编码函数
{
    int WeightNum = 27;
    LeafNum = WeightNum;
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*字符集*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*字符集对应的权值*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNum权值对应的哈夫曼树中的结点总数为2*WeightNum-1个
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "请输入第" << i + 1 << "个字符值：";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "请输入该字符的权值或频度：";
  		//cin >> Node[i].weight;    //输入权值
  		Node[i].parent = -1;      //为根结点
  		Node[i].LeftChild = -1;      //无左孩子
  		Node[i].RightChild = -1;      //无右孩子
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //表示需做WeightNum-1次合并
 	{
  		pos1 = -1;          //存放当前最小值的所在单元编号
  		pos2 = -1;          //存放当前次小值的所在单元编号
  		max1 = 32767;       //存放当前找到的最小值
  		max2 = 32767;       //存放当前找到的次小值 
		for(j = 0; j < i; j++)   //在未使用节点中选出权值最小的两个
		{      
   			if(Node[j].parent == -1)  //是否为根结点
			{         
    			if(Node[j].weight < max1)   //是否比最小值要小
    			{
     				max2 = max1;            //原最小值变为次小值
     				max1 = Node[j].weight;  //存放最小值
     				pos2 = pos1;            //修改次小值所在单元编号
     				pos1 = j;               //修改最小值所在单元编号
    			}
    			else if(Node[j].weight < max2)  //比原最小值大但比原次小值要小
     			{
      				max2 = Node[j].weight;  //存放次小值
      				pos2 = j;               //修改次小值所在的单元编号
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //修改父亲位置
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //修改儿子位置
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //表示新结点应该是根结点
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
    
    /*
	if(Node == NULL)       //哈夫曼树不在内存，从文件hfmTree中读入
 	{
  		ifstream fip;        //以二进制方式打开hfmTree.dat文件
  		fip.open("hfmTree.txt",ios::binary|ios::in);
  		if(fip.fail())       //文件打开失败
  		{
   			cout<<"文件打开失败！/n";
   			return;          //结束函数
  		}
  		fip.read((char*)&LeafNum, sizeof(LeafNum));   //读取叶子数
  		Info = new char[LeafNum];
  		Node = new HuffmanNode[2 * LeafNum - 1];
  		for(int i = 0; i < LeafNum; i++)              //读取字符信息
   			fip.read((char*)&Info[i], sizeof(Info[i]));
  		for(int i = 0; i < 2 * LeafNum - 1; i++)      //读取结点信息
   			fip.read((char*)&Node[i], sizeof(Node[i]));
 	}*/
 
 	char *Tree;          //用于存储需编码内容
 	i = 0;
	int num;
 	cout << "从文件中读取内容ing..." << endl;
 	ifstream fip1("ToBeTran.txt");
  	if(fip1.fail())      //文件不存在
  	{
   		cout << "文件打开失败!" << endl;
   		return;          //结束函数
  	}
  	char ch;
  	int k = 0;
  	while(fip1.get(ch))           
  	{
   		k++;             //计算CodeFile中代码长度
  	}
  	int ttt = k;
  	fip1.close();
 	Tree = new char[k + 1];
  	ifstream fip2("ToBeTran.txt", ios::in | ios::binary);
	fip2.getline(Tree, k + 1);
  	fip2.close();
  	Tree[k] = '/0';      //结束标志
	cout << "读取成功！" << endl;
 	ofstream fop("CodeFile.txt",ios::trunc);   //存储编码后的代码,并覆盖原文件
 	char *code;
 	code = new char[LeafNum];       //为所产生编码分配容量为LeafNum的存储空间
                                    //因为不等长编码中最长的编码一定不会超过要求编码的字符个数
 	for(int k = 0; k < ttt; k++)
	{
	 	int j, start = 0;
  		for(i = 0; i < LeafNum; i++)
		{
		  	if(Info[i] == Tree[k])  //求出该文字所在单元的编号
		  	{
				break;
			}	
		}
   		j = i;
 	 	while(Node[j].parent != -1)     //结点j非树根
  		{
   			j = Node[j].parent;         //非结点j的双亲结点
   			if(Node[j].LeftChild == i)  //是左子树，则生成代码0
			{
				code[start++] = '0';
			}           
    		else
			{
				code[start++] = '1';    //是右子树，则生成代码1
			}                          
    		i = j;
  		}
		for(i = 0; i < start / 2; i++)  //对二进制序列进行逆置
  		{
   			j = code[i];
   			code[i] = code[start- i - 1];
   			code[start - i - 1] = j;
  		}
        i = 0;
        for (int o = 0; o < start; o++)
		{
			fop << code[o];
			cout << code[o];
		}
	}
	cout << endl;
 	fop.close();
 	cout << "已编码！且存到文件CodeFile.txt中！" << endl << endl;
}

//  函数功能：利用已建好的哈夫曼树,对传输到达的CodeFile中的数据代码进行译码,
//            将译码结果存入文件TextFile中.
void HuffmanTree::Decoder()  //译码函数
{
 	int WeightNum = 27;
    LeafNum = WeightNum;
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*字符集*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*字符集对应的权值*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNum权值对应的哈夫曼树中的结点总数为2*WeightNum-1个
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "请输入第" << i + 1 << "个字符值：";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "请输入该字符的权值或频度：";
  		//cin >> Node[i].weight;    //输入权值
  		Node[i].parent = -1;      //为根结点
  		Node[i].LeftChild = -1;      //无左孩子
  		Node[i].RightChild = -1;      //无右孩子
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //表示需做WeightNum-1次合并
 	{
  		pos1 = -1;          //存放当前最小值的所在单元编号
  		pos2 = -1;          //存放当前次小值的所在单元编号
  		max1 = 32767;       //存放当前找到的最小值
  		max2 = 32767;       //存放当前找到的次小值 
		for(j = 0; j < i; j++)   //在未使用节点中选出权值最小的两个
		{      
   			if(Node[j].parent == -1)  //是否为根结点
			{         
    			if(Node[j].weight < max1)   //是否比最小值要小
    			{
     				max2 = max1;            //原最小值变为次小值
     				max1 = Node[j].weight;  //存放最小值
     				pos2 = pos1;            //修改次小值所在单元编号
     				pos1 = j;               //修改最小值所在单元编号
    			}
    			else if(Node[j].weight < max2)  //比原最小值大但比原次小值要小
     			{
      				max2 = Node[j].weight;  //存放次小值
      				pos2 = j;               //修改次小值所在的单元编号
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //修改父亲位置
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //修改儿子位置
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //表示新结点应该是根结点
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }

	i = 0;
	int k = 0;
 	j = LeafNum * 2 - 2;      //表示从根结点开始往下搜索
 	char* BitStr;
 
 	ifstream fip1("CodeFile.txt"); //利用已建好的哈夫曼树将文件CodeFile中的代码进行译码
 	if(fip1.fail())          //文件打开失败，还未编码
 	{
  		cout << "请先编码！" << endl;
  		return;
 	}
 	cout << "经译码,原内容为:";
  	char ch;
 	while(fip1.get(ch))           
 	{
  		k++;                  //计算CodeFile中代码长度
 	}
 	fip1.close(); 
 
 	BitStr = new char[k + 1];
 	ifstream fip2("CodeFile.txt");
 	k = 0;
 	while(fip2.get(ch))
 	{
  		BitStr[k] = ch;       //读取文件内容
  		k++;
 	}
 	fip2.close(); 
	int num = k;           
 	//BitStr[k] = '/0';        //结束标志符
 	if(Node == NULL)         //还未建哈夫曼树
 	{
  		cout << "请先编码!" << endl;
  		return;
 	}
 	ofstream fop("TextFile.txt",ios::out|ios::binary|ios::trunc);        //将字符形式的编码文件写入文件CodePrin中
 	for (int i = 0; i < num; i++)
	{
	 	if(BitStr[i] == '0')
   			j = Node[j].LeftChild;       //往左走
  		else
   			j = Node[j].RightChild;      //往右走
  		if(Node[j].RightChild == -1)     //到达叶子结点
  		{
   			cout << Info[j];             //输出叶子结点对应的字符
   			j = LeafNum * 2 - 2;         //表示重新从根结点开始往下搜索
   			fop << Info[j];              //存入文件
  		}
 	}
 	fop.close();
 	cout << endl << "译码成功且已存到文件TextFile.txt中！" << endl << endl;
}

//  函数功能：将文件CodeFile以紧凑格式显示在终端上，
//            每行50个代码。同时将此字符形式的编码文件写入文件CodePrin中。
void HuffmanTree::Print()  //打印代码文件函数
{
 	char ch;
 	int i = 1;  //计数 
 	ifstream fip("CodeFile.txt");  //读取文件
 	ofstream fop("CodePrin.txt");  //存储文件
 	if(fip.fail())
 	{
  		cout<<"没有文件，请先编码！/n";
		return;
 	}
 	while(fip.get(ch))
 	{
  		cout << ch;        //读取文件内容
  		fop << ch;         //存到文件中
  		if(i == 50)        //每行输出50个字符
  		{
   			cout << endl;
   			i = 0;
  		}
  		i++;
 	}
 	cout << endl << endl;
 	fip.close();           //关闭CodeFile.txt文件
 	fop.close();           //关闭CodePrin.txt文件
}

//  函数功能：将已在内存中的哈夫曼树以直观的方式(树或凹入表的形式)显示在终端上，
//            同时将此字符形式的哈夫曼树写入文件TreePrint中。
void HuffmanTree::TreePrinting()  //打印哈夫曼树函数
{
 	int WeightNum = 27;
	 char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*字符集*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*字符集对应的权值*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNum权值对应的哈夫曼树中的结点总数为2*WeightNum-1个
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "请输入第" << i + 1 << "个字符值：";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "请输入该字符的权值或频度：";
  		//cin >> Node[i].weight;    //输入权值
  		Node[i].parent = -1;      //为根结点
  		Node[i].LeftChild = -1;      //无左孩子
  		Node[i].RightChild = -1;      //无右孩子
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //表示需做WeightNum-1次合并
 	{
  		pos1 = -1;          //存放当前最小值的所在单元编号
  		pos2 = -1;          //存放当前次小值的所在单元编号
  		max1 = 32767;       //存放当前找到的最小值
  		max2 = 32767;       //存放当前找到的次小值 
		for(j = 0; j < i; j++)   //在未使用节点中选出权值最小的两个
		{      
   			if(Node[j].parent == -1)  //是否为根结点
			{         
    			if(Node[j].weight < max1)   //是否比最小值要小
    			{
     				max2 = max1;            //原最小值变为次小值
     				max1 = Node[j].weight;  //存放最小值
     				pos2 = pos1;            //修改次小值所在单元编号
     				pos1 = j;               //修改最小值所在单元编号
    			}
    			else if(Node[j].weight < max2)  //比原最小值大但比原次小值要小
     			{
      				max2 = Node[j].weight;  //存放次小值
      				pos2 = j;               //修改次小值所在的单元编号
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //修改父亲位置
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //修改儿子位置
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //表示新结点应该是根结点
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
 	LeafNum = WeightNum;
	
	if(Node == NULL)  //未建立哈夫曼树
 	{
  		cout << "请先建立哈夫曼树！" << endl;
  		return;
 	}
 	ofstream fop("TreePrint.txt",ios::trunc);
 	cout << "结点位置(权值)  " << "编码  " << "左孩子  " << "编码" << "右孩子('^'表示叶子)" << endl;
    fop << "结点位置(权值)  " << "编码  " << "左孩子  " << "编码" << "右孩子('^'表示叶子)" << endl;
	for(i = (2 * LeafNum - 2); i > LeafNum - 1; i--)   //输出哈夫曼树
 	{
  		cout << i << "(" << Node[i].weight << ")" << "--1--"
  		<< Node[i].LeftChild << "(" << Node[Node[i].LeftChild].weight << ")" << "--0--"
  		<< Node[i].RightChild << "(" << Node[Node[i].RightChild].weight << ")" << endl;
  		fop << i << "(" << Node[i].weight << ")" << "--1--"
  		<< Node[i].LeftChild << "(" << Node[Node[i].LeftChild].weight << ")" << "--0--"
  		<< Node[i].RightChild << "(" << Node[Node[i].RightChild].weight << ")" << endl;
 	}
 	for(; i >= 0; i--)
 	{
  		cout << i << ":" << Node[i].weight << "(" << Info[i] << ")---^/n";
  		fop << i << ":" << Node[i].weight << "(" << Info[i] << ")---^/n";
 	}
 	cout << endl << endl;
}

void Menu()  //菜单函数 
{
	while(1)
	{
		int choice;
		HuffmanTree HT;
		cout << "*************************" << endl; 
		cout << "* 哈夫曼码的编/译码系统 *" << endl;
		cout << "*       1、初始化       *" << endl;
		cout << "*        2、编码        *" << endl;
		cout << "*        3、译码        *" << endl;
		cout << "*    4、打印代码文件    *" << endl;
		cout << "*    5、打印哈夫曼树    *" << endl;
		cout << "*        6、退出        *" << endl;
		cout << "*************************" << endl;
		cout << "请选择要操作的选项：";
		cin >> choice;
		if (choice == 1)
		{
			int n;
			cout << "请输入字符集大小：";
			cin >> n;
			HT.Initialization(n);
		}
		else if (choice == 2)
		{
			HT.Encoder();
		}
		else if (choice == 3)
		{
			HT.Decoder();
		}
		else if (choice == 4)
		{
			HT.Print();
		}
		else if (choice == 5)
		{
			HT.TreePrinting();
		}
		else break;
	}
}

int main(int argc, char** argv)
{
	Menu();  //菜单函数 
	return 0;
}
