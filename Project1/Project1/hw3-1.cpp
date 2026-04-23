#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct Node {
	char elem=0;
	int lchild;
	int rchild;
};

//顺序表存储二叉树：
//用数组、下标实现栈


Node list[200];
int stack[200];
char inp[100];

//后序遍历打印树
void PostTraverse(int node)
{
	if (list[node].elem == 0)
		return;

	PostTraverse(list[node].lchild);
	PostTraverse(list[node].rchild);

	if(list[node].elem!=1)//不打印头结点
		printf("%c", list[node].elem);
}

int main()
{
	int cnt;
	scanf("%d", &cnt);

	//不妨设list[0]为根节点
	int Endlist = 1;
	int top=0;

	list[0].elem = 1;//标记头结点
	list[0].rchild = Endlist++;
	list[0].lchild = Endlist++;

	stack[top++] = list[0].rchild;
	stack[top++] = list[0].lchild;

	while (cin.getline(inp, 100)&&cnt)
	{
		if (strncmp(inp, "push", 4) == 0)
		{
			//出栈
			int cur=--top;

			list[stack[cur]].elem =inp[5];
			list[stack[cur]].lchild = Endlist++;
			list[stack[cur]].rchild = Endlist++;			

			int lchild = list[stack[cur]].rchild;
			int rchild = list[stack[cur]].lchild;
			//入栈
			stack[top++] = lchild;
			stack[top++] = rchild;

			cnt--;
		}
		else if (strncmp(inp, "pop", 3) == 0)
		{
			top--;
			//如果p是左，则更新p为右
			//p为右，更新p为父的父
			//当左右均为NULL，无法判断
		}

		if (top == 1)
			break;
	}


	PostTraverse(0);

	return 0;
}