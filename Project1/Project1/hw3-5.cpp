//最近祖先节点
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

struct Node {
	int parent = -1;
	vector<int> SubNodes;
};

Node list[1010];
int parent[1010];

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int N, M;
		scanf("%d%d",&N,&M);
		for (int i = 0; i < N - 1; i++)
		{
			int root, child;
			scanf("%d%d", &root, &child);

			list[root].SubNodes.push_back(child);
			list[child].parent = root;
		}

		for (int i = 0; i < M; i++)
		{
			memset(parent, 0, sizeof(int) * N+1);
			
			int kid1, kid2;
			scanf("%d%d", &kid1, &kid2);

			//从kid1向上遍历，记录经历的parent
			int cur = kid1;
			while (1)
			{
				parent[cur] = 1;
				if (list[cur].parent != -1)
					cur = list[cur].parent;
				else
					break;
			}

			cur = kid2;
			while (cur != -1 && !parent[cur])
			{
				cur = list[cur].parent;
			}

			printf("%d\n", cur);
		}

		for (int i = 0; i < N+1; i++)
		{
			list[i] = Node();
		}
	}


	return 0;
}


//TLE是由于边界条件、重置clear的时候不要重置太大

