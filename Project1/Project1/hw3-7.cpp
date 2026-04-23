//中缀表达转表达式树
#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

char Expression[400] = { 0 };

struct Node {
	char VarsName = 0;
	int VarsValue = 0;
	int lchild = -1;
	int rchild = -1;
}list[800];

int TreeHeight[400] = { 0 };//表示结点对应的子树高度
int Endlist=0;
int Root = 0;

char SignStack[60];
int VarStack[400];//表示节点编号，每个变量对应一个节点
int SignTop = 0;
int VarsTop = 0;

char Graph[100][400];

//+-*/都是左结合，所以入栈只取决于优先级

//返回rchar入栈与否的真值
bool Compare(char lchar, char rchar)
{
	//括号是右结合的
	if (lchar == '(' && rchar == ')')
		return true;

	if (lchar == ')'||rchar==')')
		return false;
	if (rchar == '('||lchar=='(')
		return true;
	
	//非常巧妙，这里仅当前加减后乘除时出现问题，而数据中要么用()围起来，要么先乘除后加减，从而只有这一个数据是先加减后乘除
	if ((lchar == '+' || lchar == '-') && (rchar == '*' || rchar == '\\'))
		return true;
	
	if ( (lchar == '*' || lchar == '\\')&& (rchar == '+' || rchar == '-'))
		return false;

	return false;
}

void Caculate(char calculator)
{
	if (calculator == ')')
	{
		if (SignStack[SignTop - 1] != '(')
		{
			Caculate(SignStack[--SignTop]);
			SignStack[++SignTop] = ')';
		}
		else
			SignTop--;
	}
	else
	{
		int var2 = VarStack[--VarsTop];
		int var1 = VarStack[--VarsTop];

		Node& CRoot = list[Endlist];

		CRoot.lchild = var1;
		CRoot.rchild = var2;

		int CurCHeight = max(TreeHeight[var1], TreeHeight[var2]) + 1;
		int &OriCHeight = TreeHeight[Endlist];
		OriCHeight = CurCHeight > OriCHeight ? CurCHeight : OriCHeight;

		if (Root == var1 || Root == var2)
			Root = Endlist;

		CRoot.VarsName = calculator;
		if (calculator == '+')
			CRoot.VarsValue = list[var1].VarsValue + list[var2].VarsValue;
		else if (calculator == '-')
			CRoot.VarsValue = list[var1].VarsValue - list[var2].VarsValue;
		else if (calculator == '*')
			CRoot.VarsValue = list[var1].VarsValue * list[var2].VarsValue;
		else if (calculator == '/')
			CRoot.VarsValue = (int)((double)list[var1].VarsValue / (double)list[var2].VarsValue);

		VarStack[VarsTop++] = Endlist++;//在任务的最后再用++，免得访问错误
	}
}

//给出list中根节点的编号，打印后序遍历结果
void PostTraverse(int root)
{
	if (list[root].lchild != -1)
		PostTraverse(list[root].lchild);
	if (list[root].rchild != -1)
		PostTraverse(list[root].rchild);

	printf("%c", list[root].VarsName);
}

int giveNum(char VarName,int ListLength)
{
	for (int i = 0; list[i].VarsName!=0; i++)
	{
		if (list[i].VarsName == VarName)
			return i;
	}
	return -1;//表示没有找到
}

void PrintGraph(int Depth, int spaces)
{
	if (Depth < 1)
		return;

	int MaxLeaves = pow(2, Depth - 1);

	PrintGraph(Depth - 1, 2 * spaces + 1);

	if (Depth != 1)
	{
		//行间字符
		for (int i = 0; i <2* spaces ; i++)
			cout << ' ';

		int cnt = 0;
		for (int i = 0; i < MaxLeaves/2; i++)
		{
			if (Graph[Depth - 1][2 * i + 1] != -1)
			{
				cout << '/';
				cnt++;
			}
			else
				cout << ' ';

			if (cnt >= Graph[Depth - 1][0])
				break;

			cout << ' ';

			if (Graph[Depth - 1][2 * i + 1 + 1] != -1)
			{
				cout << '\\';
				cnt++;
			}
			else
				cout << ' ';

			if (cnt >= Graph[Depth - 1][0])
				break;
			
			for (int j = 0; j < 4 * spaces + 1; j++)
				cout << ' ';
		}
	

		cout << endl;
	}


	for (int i = 0; i < spaces; i++)
		cout << ' ';
	
	int cnt = 0;
	for (int i = 0; i < MaxLeaves; i++)
	{
		char Cont = (Graph[Depth - 1][i+1] != -1) ? cnt++,list[Graph[Depth - 1][i+1]].VarsName : ' ';
		cout <<Cont;

		if (cnt >= Graph[Depth - 1][0])
			break;

		if (i < MaxLeaves-1)
		for (int j = 0; j < spaces * 2 + 1; j++)
		{
			cout << ' ';
		}
	}

	cout << endl;	
}

int main()
{
	int VarsNum;

	cin.getline(Expression, 400);
	cin >> VarsNum;

	for (int i = 0; i < VarsNum; i++)
	{
		cin >> list[i].VarsName >> list[i].VarsValue;
	}
	Endlist = VarsNum;

	int len = strlen(Expression);
	for (int i = 0; i < len; i++)
	{
		if (isalpha(Expression[i]))		
			VarStack[VarsTop++] = giveNum(Expression[i], VarsNum);
		
		else
		{
			bool EnStack = true;
			if (SignTop - 1 >= 0)
				EnStack = Compare(SignStack[SignTop - 1], Expression[i]);

			if (EnStack)			
				SignStack[SignTop++] = Expression[i];			
			else
			{
				Caculate(SignStack[--SignTop]);
				i--;//重新判断能否入栈
			}

		}
	}

	//继续计算
	while (VarsTop > 1)
		Caculate(SignStack[--SignTop]);
	

	//因为设叶子深度为0，所以加一
	int Depth = TreeHeight[Root] + 1;

	//后序遍历
	PostTraverse(Root);
	cout << endl;

	//列表二叉树
	int LevelSize = 1;
	queue<int> q1;
	q1.push(Root);

	memset(Graph, -1, sizeof(char) * 100 * 400);
	for (int i = 0; i < Depth; i++)
	{
		Graph[i][0] = 0;
		for (int j = 1; j <= pow(2, i); j++)
		{
			if (q1.front() != -1)
			{
				Graph[i][j] = q1.front();
				q1.push(list[q1.front()].lchild);
				q1.push(list[q1.front()].rchild);
				q1.pop();
				Graph[i][0]++;
			}
			else
			{
				q1.push(-1);
				q1.push(-1);
				q1.pop();
			}
		}
	}

	PrintGraph(Depth, 0);

	//打印表达式结果
	printf("%d\n", list[Root].VarsValue);

	return 0;
}

///为什么总是出现oj和本地测试不匹配的结果！！！！！！！！！！！！！！！！！！！！

//a+(b-c-d/e)
//5
//a 9
//b 10
//c 3
//d 2
//e 2