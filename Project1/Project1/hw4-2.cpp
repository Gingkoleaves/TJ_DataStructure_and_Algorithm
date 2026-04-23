#include <iostream>
#include <iomanip>

#define VertexType unsigned int
#define MAX_VERTEX_NUM 2000
using namespace std;

typedef struct ArcNode {
	int adjvex;  //该弧所指向的顶点的位置
	struct ArcNode* nextarc;//指向下一条弧的指针
}ArcNode;  //边结点类型

typedef struct VNode {
	VertexType dist=-1;
	//顶点信息
	ArcNode* firstarc = nullptr; //指向第一条依附该顶点的指针
	ArcNode* lastarc = nullptr;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;  //邻接表
	int vexnum, arcnum;
}ALGraph;


ALGraph g1;


//深度优先的搜索:当前节点、当前节点距离根节点的距离，返回遍历的节点数
int dfs(int src,int depth)
{
	if (depth > 6)return 0;

	if (g1.vertices[src].dist <=depth)
		return 0;

	int count = 0;

	if (g1.vertices[src].dist == -1)count++;
	g1.vertices[src].dist = depth;

	ArcNode* cur = g1.vertices[src].firstarc;
	while (cur != nullptr)
	{
		if (g1.vertices[cur->adjvex].dist > depth+1)//因为是图，可能有环？
		{
			count += dfs(cur->adjvex,depth+1);
		}
		cur = cur->nextarc;
	}
	return count;
}

int main()
{
	cin >> g1.vexnum >> g1.arcnum;

	int src, dst;
	for (int i = 0; i < g1.arcnum; i++)
	{
		cin >> src >> dst;
		//尾插法
		if (g1.vertices[src].lastarc == nullptr)
		{
			g1.vertices[src].firstarc = new ArcNode{ dst };
			g1.vertices[src].lastarc = g1.vertices[src].firstarc;
		}
		else
		{
			g1.vertices[src].lastarc->nextarc = new ArcNode{ dst };
			g1.vertices[src].lastarc = g1.vertices[src].lastarc->nextarc;
		}

		if (g1.vertices[dst].lastarc == nullptr)
		{
			g1.vertices[dst].firstarc = new ArcNode{ src };
			g1.vertices[dst].lastarc = g1.vertices[dst].firstarc;
		}
		else
		{
			g1.vertices[dst].lastarc->nextarc = new ArcNode{ src };
			g1.vertices[dst].lastarc = g1.vertices[dst].lastarc->nextarc;
		}
	}

	for (int i = 1; i <= g1.vexnum; i++)
	{
		int res = dfs(i,0);

		cout << i << ": " << setprecision(2)<<setiosflags(ios::fixed) << ((float)res / g1.vexnum)*100 << "%" << endl;		

		//清空visited
		for (int i = 1; i <= g1.vexnum; i++)
			g1.vertices[i].dist = -1;
	}



	return 0;
}