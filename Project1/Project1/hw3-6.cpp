//求树的后序遍历
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

struct Node {
	int lchild = -1;
	int rchild = -1;
};

Node list[150];
char ForTra[160];
char MidTra[160];


//标志位不清晰：0表示空节点，-1表示非法
int giveBinaryTree(char* ForTraPos,char* MidTraPos,int SeqTraLen)
{
	if (SeqTraLen == 0)
		return 0;
	if (SeqTraLen == 1)
	{
		if (ForTraPos[0] == MidTraPos[0])
		{
			list[MidTraPos[0]].lchild = 0;
			list[MidTraPos[0]].rchild = 0;
			return MidTraPos[0];
		}
		return -1;
	}
	char* RootInMid=NULL;
	//这里是问题的根本：搜索越界，原来是strchr
	//所以能跑不能说明任何问题，只能说编译器优化的真好
	for (int i = 0; i < SeqTraLen; i++)
		if (*(MidTraPos + i) == ForTraPos[0])
		{
			RootInMid = MidTraPos + i;
			break;
		}
	RootInMid = strchr(MidTraPos, ForTraPos[0]);

	if (RootInMid == NULL)//没找到
		return -1;

	int NextForTraLen = RootInMid - MidTraPos;//这个一定为正
	int NextPostTraLen = SeqTraLen - NextForTraLen - 1;//这个可能为负，从而死循环

	int lc=giveBinaryTree(ForTraPos+1, MidTraPos, NextForTraLen);
	int rc=giveBinaryTree(ForTraPos+1+NextForTraLen, MidTraPos+1+ NextForTraLen, NextPostTraLen);


	if (lc != -1 && rc != -1)
	{
		list[(int)ForTraPos[0]].lchild = lc;
		list[(int)ForTraPos[0]].rchild = rc;

		return ForTraPos[0];
	}
	else
		return -1;
}

void PostTraverse(int root)
{
	if(list[root].lchild!=0)
		PostTraverse(list[root].lchild);
	if(list[root].rchild!=0)
		PostTraverse(list[root].rchild);

	if(isalnum(root))
		printf("%c", root);
}

int main()
{
	char cmdline[130];
	//scanf读取不了EOF
	while (cin.getline(cmdline,130))
	{
		memset(ForTra, 0, sizeof(char) * 160);
		memset(MidTra, 0, sizeof(char) * 160);
		sscanf(cmdline,"%s%s", ForTra, MidTra);

		if (strlen(ForTra) == strlen(MidTra)) {
			int root = giveBinaryTree(ForTra, MidTra, strlen(ForTra));
			if (root == -1)
			{
				printf("Error\n");
			}
			else
			{
				PostTraverse(root);
				printf("\n");
			}
		}
		else
			printf("Error\n");

		for (int i = 0; i < 150; i++)
		{
			list[i] = Node();
		}

	}


	return 0;
}

/*
xvMI3bqUsDWeHON5S 3IqbDWsUMvONHexS5
PJbOiAprCov JOpACriboPv
FvKSTYJmnINtZ5 STJYmnIKv5ZtNF
NdxE1IbMVq dN1ExMbqVI
Se2NctzMvXYhf 2cNtMvzXYhefS
n9jAStqRbuN8oi nSAtqjR8Noub9i
kQTZl7yzuhFL92 TlZ7QyzhuFkL92
WvnBcmiJ4Q28aMq ncBmvJi4W8a2MQq
ofypK23JgE1sAvYUdibI pyK32fJoAs1EYvgidUIb
P3YgRC4szIVOLJQ PQJ3sz4ICVRgYOL


*/