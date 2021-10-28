#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct HuffmanNode   //����������ڵ� 
{
	int weight;      //Ȩֵ 
	int parent;      //��Ÿ��ڵ�λ�� 
	int LeftChild;   //������ӽڵ�λ�� 
	int RightChild;  //������ӽڵ�λ�� 
};

class HuffmanTree    //������������� 
{
	private:
		char *Info;         //�ַ���Ϣ 
		int LeafNum;        //Ҷ�ڵ���Ŀ 
		HuffmanNode* Node;  //�������ڵ� 
		
	public:
		HuffmanTree();        //���캯��
 		~HuffmanTree();       //��������
 		void Initialization(int WeightNum);   //��ʼ������������WeightNum��Ȩֵ����һ�ù�������
		void Encoder();       //���뺯�������ù���õĹ����������ַ����б���
 		void Decoder();       //���뺯�����Զ����ƴ���������
 		void Print();         //��ӡ�ļ����������ѱ���õı����ļ���ʾ����Ļ
 		void TreePrinting();  //��ӡ���������������������ڴ��еĹ���������ֱ�۵ķ�ʽ��ʾ���ն���	
};

HuffmanTree::HuffmanTree()  //���캯�� 
{
 	Node = NULL;  //��������ʼ��Ϊ��
 	Info = NULL;  //���ַ������ʼ��Ϊ��
 	LeafNum = 0;  //��Ҷ������ʼ��Ϊ0
}

HuffmanTree::~HuffmanTree()  //��������
{
	delete[] Info;
	delete[] Node;
}

//  �������ܣ����ն˶����ַ�����Сn���Լ�n���ַ���n��Ȩֵ,
//            ������������,������������ļ�hfmTree��.
void HuffmanTree::Initialization(int WeightNum)  //��ʼ������
{
	
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*�ַ���*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*�ַ�����Ӧ��Ȩֵ*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "�������" << i + 1 << "���ַ�ֵ��";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "��������ַ���Ȩֵ��Ƶ�ȣ�";
  		//cin >> Node[i].weight;    //����Ȩֵ
  		Node[i].parent = -1;      //Ϊ�����
  		Node[i].LeftChild = -1;      //������
  		Node[i].RightChild = -1;      //���Һ���
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�
 	{
  		pos1 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		pos2 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		max1 = 32767;       //��ŵ�ǰ�ҵ�����Сֵ
  		max2 = 32767;       //��ŵ�ǰ�ҵ��Ĵ�Сֵ 
		for(j = 0; j < i; j++)   //��δʹ�ýڵ���ѡ��Ȩֵ��С������
		{      
   			if(Node[j].parent == -1)  //�Ƿ�Ϊ�����
			{         
    			if(Node[j].weight < max1)   //�Ƿ����СֵҪС
    			{
     				max2 = max1;            //ԭ��Сֵ��Ϊ��Сֵ
     				max1 = Node[j].weight;  //�����Сֵ
     				pos2 = pos1;            //�޸Ĵ�Сֵ���ڵ�Ԫ���
     				pos1 = j;               //�޸���Сֵ���ڵ�Ԫ���
    			}
    			else if(Node[j].weight < max2)  //��ԭ��Сֵ�󵫱�ԭ��СֵҪС
     			{
      				max2 = Node[j].weight;  //��Ŵ�Сֵ
      				pos2 = j;               //�޸Ĵ�Сֵ���ڵĵ�Ԫ���
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //�޸ĸ���λ��
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //�޸Ķ���λ��
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //��ʾ�½��Ӧ���Ǹ����
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
 	LeafNum = WeightNum;
 	
	char ch;
 	cout << "�Ƿ�Ҫ�滻ԭ���ļ�(Y/N):";
 	cin >> ch;
 	if(ch == 'Y')
 	{
 		ofstream fop;   //�Զ����Ʒ�ʽ��hfmTree.dat�ļ���������������ʱ����ԭ�ļ�
 		fop.open("hfmTree.txt", ios::out|ios::binary|ios::trunc);
 		if(fop.fail())  //�ļ���ʧ��
		{                    
  			cout << "�ļ���ʧ�ܣ�" << endl;
  		}
  		//fop << WeightNum;
 		fop.write((char*)&WeightNum, sizeof(WeightNum));  //д��WeightNum
 		for(i = 0; i < WeightNum; i++)           //�Ѹ��ַ���Ϣд���ļ�
 		{
  			fop.write((char*)&Info[i], sizeof(Info[i]));
  			flush(cout);
 		}
 		for(i = 0; i < 2 * WeightNum - 1; i++)  //�Ѹ����ڵ�����д���ļ�
 		{
  			fop.write((char*)&Node[i], sizeof(Node[i]));
  			flush(cout);
 		}
 		fop.close();            //�ر��ļ�
 	}
 	cout << "���������ѹ������!" << endl << endl;
}


//  �������ܣ������ѽ����õĹ����������粻���ڴ棬����ļ�hfmTree�ж��룩��
//            ���ļ�ToBeTran�е����Ľ��б���,Ȼ�󽫽�������(����)���ļ�CodeFile��.
void HuffmanTree::Encoder()  //���뺯��
{
    int WeightNum = 27;
    LeafNum = WeightNum;
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*�ַ���*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*�ַ�����Ӧ��Ȩֵ*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "�������" << i + 1 << "���ַ�ֵ��";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "��������ַ���Ȩֵ��Ƶ�ȣ�";
  		//cin >> Node[i].weight;    //����Ȩֵ
  		Node[i].parent = -1;      //Ϊ�����
  		Node[i].LeftChild = -1;      //������
  		Node[i].RightChild = -1;      //���Һ���
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�
 	{
  		pos1 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		pos2 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		max1 = 32767;       //��ŵ�ǰ�ҵ�����Сֵ
  		max2 = 32767;       //��ŵ�ǰ�ҵ��Ĵ�Сֵ 
		for(j = 0; j < i; j++)   //��δʹ�ýڵ���ѡ��Ȩֵ��С������
		{      
   			if(Node[j].parent == -1)  //�Ƿ�Ϊ�����
			{         
    			if(Node[j].weight < max1)   //�Ƿ����СֵҪС
    			{
     				max2 = max1;            //ԭ��Сֵ��Ϊ��Сֵ
     				max1 = Node[j].weight;  //�����Сֵ
     				pos2 = pos1;            //�޸Ĵ�Сֵ���ڵ�Ԫ���
     				pos1 = j;               //�޸���Сֵ���ڵ�Ԫ���
    			}
    			else if(Node[j].weight < max2)  //��ԭ��Сֵ�󵫱�ԭ��СֵҪС
     			{
      				max2 = Node[j].weight;  //��Ŵ�Сֵ
      				pos2 = j;               //�޸Ĵ�Сֵ���ڵĵ�Ԫ���
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //�޸ĸ���λ��
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //�޸Ķ���λ��
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //��ʾ�½��Ӧ���Ǹ����
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
    
    /*
	if(Node == NULL)       //�������������ڴ棬���ļ�hfmTree�ж���
 	{
  		ifstream fip;        //�Զ����Ʒ�ʽ��hfmTree.dat�ļ�
  		fip.open("hfmTree.txt",ios::binary|ios::in);
  		if(fip.fail())       //�ļ���ʧ��
  		{
   			cout<<"�ļ���ʧ�ܣ�/n";
   			return;          //��������
  		}
  		fip.read((char*)&LeafNum, sizeof(LeafNum));   //��ȡҶ����
  		Info = new char[LeafNum];
  		Node = new HuffmanNode[2 * LeafNum - 1];
  		for(int i = 0; i < LeafNum; i++)              //��ȡ�ַ���Ϣ
   			fip.read((char*)&Info[i], sizeof(Info[i]));
  		for(int i = 0; i < 2 * LeafNum - 1; i++)      //��ȡ�����Ϣ
   			fip.read((char*)&Node[i], sizeof(Node[i]));
 	}*/
 
 	char *Tree;          //���ڴ洢���������
 	i = 0;
	int num;
 	cout << "���ļ��ж�ȡ����ing..." << endl;
 	ifstream fip1("ToBeTran.txt");
  	if(fip1.fail())      //�ļ�������
  	{
   		cout << "�ļ���ʧ��!" << endl;
   		return;          //��������
  	}
  	char ch;
  	int k = 0;
  	while(fip1.get(ch))           
  	{
   		k++;             //����CodeFile�д��볤��
  	}
  	int ttt = k;
  	fip1.close();
 	Tree = new char[k + 1];
  	ifstream fip2("ToBeTran.txt", ios::in | ios::binary);
	fip2.getline(Tree, k + 1);
  	fip2.close();
  	Tree[k] = '/0';      //������־
	cout << "��ȡ�ɹ���" << endl;
 	ofstream fop("CodeFile.txt",ios::trunc);   //�洢�����Ĵ���,������ԭ�ļ�
 	char *code;
 	code = new char[LeafNum];       //Ϊ�����������������ΪLeafNum�Ĵ洢�ռ�
                                    //��Ϊ���ȳ���������ı���һ�����ᳬ��Ҫ�������ַ�����
 	for(int k = 0; k < ttt; k++)
	{
	 	int j, start = 0;
  		for(i = 0; i < LeafNum; i++)
		{
		  	if(Info[i] == Tree[k])  //������������ڵ�Ԫ�ı��
		  	{
				break;
			}	
		}
   		j = i;
 	 	while(Node[j].parent != -1)     //���j������
  		{
   			j = Node[j].parent;         //�ǽ��j��˫�׽��
   			if(Node[j].LeftChild == i)  //���������������ɴ���0
			{
				code[start++] = '0';
			}           
    		else
			{
				code[start++] = '1';    //���������������ɴ���1
			}                          
    		i = j;
  		}
		for(i = 0; i < start / 2; i++)  //�Զ��������н�������
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
 	cout << "�ѱ��룡�Ҵ浽�ļ�CodeFile.txt�У�" << endl << endl;
}

//  �������ܣ������ѽ��õĹ�������,�Դ��䵽���CodeFile�е����ݴ����������,
//            �������������ļ�TextFile��.
void HuffmanTree::Decoder()  //���뺯��
{
 	int WeightNum = 27;
    LeafNum = WeightNum;
	char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*�ַ���*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*�ַ�����Ӧ��Ȩֵ*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "�������" << i + 1 << "���ַ�ֵ��";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "��������ַ���Ȩֵ��Ƶ�ȣ�";
  		//cin >> Node[i].weight;    //����Ȩֵ
  		Node[i].parent = -1;      //Ϊ�����
  		Node[i].LeftChild = -1;      //������
  		Node[i].RightChild = -1;      //���Һ���
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�
 	{
  		pos1 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		pos2 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		max1 = 32767;       //��ŵ�ǰ�ҵ�����Сֵ
  		max2 = 32767;       //��ŵ�ǰ�ҵ��Ĵ�Сֵ 
		for(j = 0; j < i; j++)   //��δʹ�ýڵ���ѡ��Ȩֵ��С������
		{      
   			if(Node[j].parent == -1)  //�Ƿ�Ϊ�����
			{         
    			if(Node[j].weight < max1)   //�Ƿ����СֵҪС
    			{
     				max2 = max1;            //ԭ��Сֵ��Ϊ��Сֵ
     				max1 = Node[j].weight;  //�����Сֵ
     				pos2 = pos1;            //�޸Ĵ�Сֵ���ڵ�Ԫ���
     				pos1 = j;               //�޸���Сֵ���ڵ�Ԫ���
    			}
    			else if(Node[j].weight < max2)  //��ԭ��Сֵ�󵫱�ԭ��СֵҪС
     			{
      				max2 = Node[j].weight;  //��Ŵ�Сֵ
      				pos2 = j;               //�޸Ĵ�Сֵ���ڵĵ�Ԫ���
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //�޸ĸ���λ��
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //�޸Ķ���λ��
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //��ʾ�½��Ӧ���Ǹ����
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }

	i = 0;
	int k = 0;
 	j = LeafNum * 2 - 2;      //��ʾ�Ӹ���㿪ʼ��������
 	char* BitStr;
 
 	ifstream fip1("CodeFile.txt"); //�����ѽ��õĹ����������ļ�CodeFile�еĴ����������
 	if(fip1.fail())          //�ļ���ʧ�ܣ���δ����
 	{
  		cout << "���ȱ��룡" << endl;
  		return;
 	}
 	cout << "������,ԭ����Ϊ:";
  	char ch;
 	while(fip1.get(ch))           
 	{
  		k++;                  //����CodeFile�д��볤��
 	}
 	fip1.close(); 
 
 	BitStr = new char[k + 1];
 	ifstream fip2("CodeFile.txt");
 	k = 0;
 	while(fip2.get(ch))
 	{
  		BitStr[k] = ch;       //��ȡ�ļ�����
  		k++;
 	}
 	fip2.close(); 
	int num = k;           
 	//BitStr[k] = '/0';        //������־��
 	if(Node == NULL)         //��δ����������
 	{
  		cout << "���ȱ���!" << endl;
  		return;
 	}
 	ofstream fop("TextFile.txt",ios::out|ios::binary|ios::trunc);        //���ַ���ʽ�ı����ļ�д���ļ�CodePrin��
 	for (int i = 0; i < num; i++)
	{
	 	if(BitStr[i] == '0')
   			j = Node[j].LeftChild;       //������
  		else
   			j = Node[j].RightChild;      //������
  		if(Node[j].RightChild == -1)     //����Ҷ�ӽ��
  		{
   			cout << Info[j];             //���Ҷ�ӽ���Ӧ���ַ�
   			j = LeafNum * 2 - 2;         //��ʾ���´Ӹ���㿪ʼ��������
   			fop << Info[j];              //�����ļ�
  		}
 	}
 	fop.close();
 	cout << endl << "����ɹ����Ѵ浽�ļ�TextFile.txt�У�" << endl << endl;
}

//  �������ܣ����ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�
//            ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�
void HuffmanTree::Print()  //��ӡ�����ļ�����
{
 	char ch;
 	int i = 1;  //���� 
 	ifstream fip("CodeFile.txt");  //��ȡ�ļ�
 	ofstream fop("CodePrin.txt");  //�洢�ļ�
 	if(fip.fail())
 	{
  		cout<<"û���ļ������ȱ��룡/n";
		return;
 	}
 	while(fip.get(ch))
 	{
  		cout << ch;        //��ȡ�ļ�����
  		fop << ch;         //�浽�ļ���
  		if(i == 50)        //ÿ�����50���ַ�
  		{
   			cout << endl;
   			i = 0;
  		}
  		i++;
 	}
 	cout << endl << endl;
 	fip.close();           //�ر�CodeFile.txt�ļ�
 	fop.close();           //�ر�CodePrin.txt�ļ�
}

//  �������ܣ��������ڴ��еĹ���������ֱ�۵ķ�ʽ(����������ʽ)��ʾ���ն��ϣ�
//            ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�TreePrint�С�
void HuffmanTree::TreePrinting()  //��ӡ������������
{
 	int WeightNum = 27;
	 char str[] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z'}; /*�ַ���*/
	int fnum[] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1}; /*�ַ�����Ӧ��Ȩֵ*/

	int i, j, pos1, pos2, max1, max2;
	Info = new char[2 * WeightNum - 1];
	//WeightNumȨֵ��Ӧ�Ĺ��������еĽ������Ϊ2*WeightNum-1��
	Node = new HuffmanNode[2 * WeightNum - 1];  
	for (i = 0; i < WeightNum; i++)
	{
		//cout << "�������" << i + 1 << "���ַ�ֵ��";
		//cin >> Info[i];
		Info[i] = str[i];
		Node[i].weight = fnum[i];
  		//cout << "��������ַ���Ȩֵ��Ƶ�ȣ�";
  		//cin >> Node[i].weight;    //����Ȩֵ
  		Node[i].parent = -1;      //Ϊ�����
  		Node[i].LeftChild = -1;      //������
  		Node[i].RightChild = -1;      //���Һ���
	}
	for(i = WeightNum; i < 2 * WeightNum - 1; i++) //��ʾ����WeightNum-1�κϲ�
 	{
  		pos1 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		pos2 = -1;          //��ŵ�ǰ��Сֵ�����ڵ�Ԫ���
  		max1 = 32767;       //��ŵ�ǰ�ҵ�����Сֵ
  		max2 = 32767;       //��ŵ�ǰ�ҵ��Ĵ�Сֵ 
		for(j = 0; j < i; j++)   //��δʹ�ýڵ���ѡ��Ȩֵ��С������
		{      
   			if(Node[j].parent == -1)  //�Ƿ�Ϊ�����
			{         
    			if(Node[j].weight < max1)   //�Ƿ����СֵҪС
    			{
     				max2 = max1;            //ԭ��Сֵ��Ϊ��Сֵ
     				max1 = Node[j].weight;  //�����Сֵ
     				pos2 = pos1;            //�޸Ĵ�Сֵ���ڵ�Ԫ���
     				pos1 = j;               //�޸���Сֵ���ڵ�Ԫ���
    			}
    			else if(Node[j].weight < max2)  //��ԭ��Сֵ�󵫱�ԭ��СֵҪС
     			{
      				max2 = Node[j].weight;  //��Ŵ�Сֵ
      				pos2 = j;               //�޸Ĵ�Сֵ���ڵĵ�Ԫ���
     			} 
    		}	
  		}
		Node[pos1].parent = i;      //�޸ĸ���λ��
  		Node[pos2].parent = i;
  		Node[i].LeftChild = pos1;   //�޸Ķ���λ��
  		Node[i].RightChild = pos2;
  		Node[i].parent = -1;        //��ʾ�½��Ӧ���Ǹ����
  		Node[i].weight = Node[pos1].weight + Node[pos2].weight;
    }
 	LeafNum = WeightNum;
	
	if(Node == NULL)  //δ������������
 	{
  		cout << "���Ƚ�������������" << endl;
  		return;
 	}
 	ofstream fop("TreePrint.txt",ios::trunc);
 	cout << "���λ��(Ȩֵ)  " << "����  " << "����  " << "����" << "�Һ���('^'��ʾҶ��)" << endl;
    fop << "���λ��(Ȩֵ)  " << "����  " << "����  " << "����" << "�Һ���('^'��ʾҶ��)" << endl;
	for(i = (2 * LeafNum - 2); i > LeafNum - 1; i--)   //�����������
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

void Menu()  //�˵����� 
{
	while(1)
	{
		int choice;
		HuffmanTree HT;
		cout << "*************************" << endl; 
		cout << "* ��������ı�/����ϵͳ *" << endl;
		cout << "*       1����ʼ��       *" << endl;
		cout << "*        2������        *" << endl;
		cout << "*        3������        *" << endl;
		cout << "*    4����ӡ�����ļ�    *" << endl;
		cout << "*    5����ӡ��������    *" << endl;
		cout << "*        6���˳�        *" << endl;
		cout << "*************************" << endl;
		cout << "��ѡ��Ҫ������ѡ�";
		cin >> choice;
		if (choice == 1)
		{
			int n;
			cout << "�������ַ�����С��";
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
	Menu();  //�˵����� 
	return 0;
}
