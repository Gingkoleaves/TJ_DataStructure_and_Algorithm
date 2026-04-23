#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

// 用两个栈读取两棵树，在输入时定位根节点
// 根节点入栈，每次操作取一个节点，看子节点是否同构
// 不同构则结束；同构则将左右节点依次入栈（bfs方式）

//实际上，就是不区分左右地记录树，看两个数是否相同

struct Node {
	char elem=0;
	int lchild=-1;
	int rchild=-1;
};

Node list[20500];
Node list2[20500];

int stack[20500];
int stack2[20500];

int flags[20500] = { 0 };


bool is_isomorphic(int root1, int root2)
{
	if (list[root1].elem == 0 && list2[root2].elem == 0)
		return true;

	if (list[root1].elem != list2[root2].elem)
		return false;

	return (is_isomorphic(list[root1].lchild, list2[root2].lchild) && is_isomorphic(list[root1].rchild, list2[root2].rchild)) ||
		(is_isomorphic(list[root1].rchild, list2[root2].lchild) && is_isomorphic(list[root1].lchild, list2[root2].rchild));
}
//
//int bfs(int root, Node* list)
//{
//	int depth=0;
//	queue<int> q;
//
//	q.push(root);
//	
//	while (!q.empty())
//	{
//		int levelsize = q.size();
//		depth++;
//
//		for (int i = 0; i < levelsize; i++)
//		{
//			int elem=q.front();
//
//			q.pop();
//
//			if (list[elem].elem)q.push(list[elem].lchild);
//			if (list[elem].elem)q.push(list[elem].rchild);
//			
//		}
//
//	}
//
//	//会遍历到空节点层
//	return --depth;
//}

int dfs(int root, Node* list)
{
	int cnt = 0;
	if (list[root].elem)
	{
		cnt++;
		cnt += max(dfs(list[root].lchild, list), dfs(list[root].rchild, list));
	}

	return cnt;
}

int main()
{
	int length;
	scanf("%d", &length);
	int EndList = length;

	cin.ignore();

	int root=0;
	for (int i = 0; i < length; i++)
	{
		char elem;
		char lchild[10];
		char rchild[10];

		int lc,rc;
		char cmd[100];
		cin.getline(cmd, 100);

		sscanf(cmd,"%c %s %s",&elem,lchild,rchild);

		if (strcmp(lchild, "-") == 0)
			lc = EndList++;
		else lc = atoi(lchild);

		if (strcmp(rchild, "-") == 0)
			rc = EndList++;
		else rc = atoi(rchild);

		list[i].elem = elem;
		list[i].lchild = lc;
		list[i].rchild = rc;	
	}

	int length2;
	scanf("%d", &length2);

	EndList = length2;
	cin.ignore();

	for (int i = 0; i < length2; i++)
	{
		char elem;
		char lchild[10];
		char rchild[10];

		int lc, rc;
		char cmd[100];
		cin.getline(cmd, 100);

		sscanf(cmd, "%c %s %s", &elem, lchild, rchild);

		if (strcmp(lchild, "-") == 0)
			lc = EndList++;
		else lc = atoi(lchild);

		if (strcmp(rchild, "-") == 0)
			rc = EndList++;
		else rc = atoi(rchild);

		list2[i].elem = elem;
		list2[i].lchild = lc;
		list2[i].rchild = rc;
	}

	//找头结点
	for (int i = 0; i < length; i++)
	{
		if (list[i].lchild != -1)
			flags[list[i].lchild] = 1;

		if (list[i].rchild != -1)
			flags[list[i].rchild] = 1;
	}

	for (int i = 0; i < length; i++)
	{
		if (!flags[i])root = i;
	}

	int root2 = 0;
	memset(flags,0, sizeof(int) * 10500);
	for (int i = 0; i < length2; i++)
	{
		if (list2[i].lchild != -1)
			flags[list2[i].lchild] = 1;

		if (list2[i].rchild != -1)
			flags[list2[i].rchild] = 1;
	}

	for (int i = 0; i < length2; i++)
	{
		if (!flags[i])
		{
			root2 = i;
			break;
		}
	}

	int depth1 = dfs(root, list);
	int depth2 = dfs(root2,list2);


	//递归检查
	if (is_isomorphic(root, root2))
		printf("Yes\n");
	else printf("No\n");

	printf("%d\n%d\n", depth1, depth2);





	return 0;
}