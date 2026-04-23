#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <vector>


using namespace std;


struct Node {
	int parent = -1;
	vector<int> SubNodes;

	void clear()
	{
		SubNodes.clear();
		parent = -1;
	}
};

int listd[20010];
Node list[20010];

int dp(int root)
{
	if (listd[root] != -1)
		return listd[root];	

	int curheight = -1;


	if (!list[root].SubNodes.empty())
		curheight = listd[root] != -1? listd[root]:dp(list[root].SubNodes[0]);

	if (( list[root].parent != -1)&&(*(list[list[root].parent].SubNodes.end() - 1) != root))
	{
		//要找root是第几个孩子
		int cnt = 0;
		for (int i : list[list[root].parent].SubNodes)
		{
			if (i == root)break;
			cnt++;
		}
		curheight = max(listd[root] != -1 ? listd[root] : dp(list[list[root].parent].SubNodes[cnt+1]), curheight);
	}	

	listd[root] = curheight+1;
	return curheight+1;
}


char cmd[20500];
int main()
{
	int kase = 1;		
	memset(listd, -1, sizeof(int) * 20010);

	while (cin.getline(cmd, 20500) && cmd[0] != '#'&& kase<5000)
	{
		int CurP = 0;
		int NextP = 0;
		int EndList = 1;

		int OriHeight = 0;
		int CurHeight = 0;
		int num = 1;

		//读树
		for (unsigned int i = 0; i < strlen(cmd); i++)
		{
			if (cmd[i] == 'd')
			{
				NextP = EndList++;
				list[NextP].parent = CurP;
				list[CurP].SubNodes.push_back(NextP);

				CurP = NextP;
				CurHeight++;

				num++;
			}
			else if (cmd[i] == 'u')
			{
				CurP = list[CurP].parent;
				CurHeight--;
			}

			if (CurHeight > OriHeight)
				OriHeight = CurHeight;
		}

		int LaterHeight=dp(0);
		printf("Tree %d: %d => %d\n",kase++, OriHeight, LaterHeight);

		//清零
		for (unsigned int i = 0; i< num+1; i++)
			list[i].clear();

		memset(listd, -1, sizeof(int) * (num+1));

	}
	return 0;
}


//有简单的方法，就不要在同等复杂度选择系数更大的方法

#ifdef His

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define N 10000
typedef char TElemType;

struct Node {
	TElemType data;
	int leftChild = -1, rightChild = -1;
};

typedef Node Bitree[N];
Bitree btree;

typedef Node* SElemType;
struct SqStack {
	SElemType* base;
	SElemType* top;
	int stacksize;
};

void InitStack(SqStack& S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

bool StackEmpty(SqStack S) {
	return S.top == S.base;
}

void Push(SqStack& S, SElemType e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
}

bool Pop(SqStack& S, SElemType& e) {
	if (StackEmpty(S)) return false;
	e = *--S.top;
	return true;
}

int Depth(Bitree T, Bitree& bt) {
	if (T->leftChild == -1 && T->rightChild == -1) return 1;
	int leftDepth = T->leftChild != -1 ? Depth(bt + T->leftChild, bt) : 0;
	int rightDepth = T->rightChild != -1 ? Depth(bt + T->rightChild, bt) : 0;
	return max(leftDepth, rightDepth) + 1;
}

int main() {
	string sr;
	int treeCount = 1;
	SqStack S;
	InitStack(S);

	while (cin >> sr && sr[0] != '#') {
		int maxDepth1 = 0, currentDepth = 0, totalNodes = 1;
		for (char c : sr) {
			if (c == 'd') {
				currentDepth++;
				maxDepth1 = max(maxDepth1, currentDepth);
				totalNodes++;
			}
			else if (c == 'u') {
				currentDepth--;
			}
		}

		for (int i = 0; i < totalNodes; i++) {
			btree[i].leftChild = btree[i].rightChild = -1;
		}

		Node* p = btree;
		int cur = 1;
		bool setRight = false;

		Push(S, p);

		for (char c : sr) {
			if (c == 'd') {
				if (!setRight) p->leftChild = cur;
				else p->rightChild = cur;

				p = btree + cur++;
				Push(S, p);
				setRight = false;
			}
			else if (c == 'u') {
				Pop(S, p);
				setRight = true;
			}
		}

		int maxDepth2 = Depth(btree, btree) - 1;
		cout << "Tree " << treeCount++ << ": " << maxDepth1 << " => " << maxDepth2 << endl;
	}

	return 0;
}
#endif
