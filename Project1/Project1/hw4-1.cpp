#include <iostream>
#include <queue>
#include <sstream>

#define VertexType int
#define MAX_VERTEX_NUM 1000
using namespace std;

//邻接表
typedef struct ArcNode {
	int adjvex;  //该弧所指向的顶点的位置
	struct ArcNode* nextarc;//指向下一条弧的指针
}ArcNode;  //边结点类型

typedef struct VNode {
	VertexType data;
	int visited = 0;
	//顶点信息
	ArcNode* firstarc=nullptr; //指向第一条依附该顶点的指针
	ArcNode* lastarc = nullptr;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;  //邻接表
	int vexnum, arcnum;
}ALGraph;


ALGraph g1;

ostringstream buffer;

//遍历过的是点
int dfs(int src)
{
	if (g1.vertices[src].visited == 1)
		return 0;

	g1.vertices[src].visited = 1;
	int count = 0;
	count++;
	buffer << src << ' ';

	ArcNode* cur = g1.vertices[src].firstarc;
	while (cur != nullptr)
	{
		if (!(g1.vertices[cur->adjvex].visited))//因为是图，可能有环？
		{
			count+=dfs(cur->adjvex);
		}
		cur = cur->nextarc;
	}
	return count;
}

int bfs(int src)
{
	if (g1.vertices[src].visited == 1)
		return 0;

	queue<int> q1;
	q1.push(src);
	buffer << src << ' ';
	g1.vertices[src].visited = 1;

	int count = 1;

	while (!q1.empty())
	{
		int cur = q1.front();
		q1.pop();

		ArcNode* curptr = g1.vertices[cur].firstarc;
		while (curptr != nullptr)
		{
			if (!g1.vertices[curptr->adjvex].visited)//因为是图，可能有环？
			{
				g1.vertices[curptr->adjvex].visited = 1;
				buffer << curptr->adjvex << ' ';
				q1.push(curptr->adjvex);
				count++;
			}
			curptr = curptr->nextarc;
		}
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

	//dfs
	int remain = g1.vexnum;
	buffer << "{";
	for (int i = 0; i < g1.vexnum; i++)
	{
		int res=dfs(i);
		if (res != 0)
		{
			buffer.seekp(-1, ios::cur);
			buffer << "}";

			if (remain -= res)
				buffer << "{";
			else
				buffer << endl;
		}
	}
	cout << buffer.str();

	//清空visited
	for (int i = 0; i < g1.vexnum; i++)
		g1.vertices[i].visited = 0;
	buffer.str("");

	//bfs
	remain = g1.vexnum;
	buffer << "{";
	for (int i = 0; i < g1.vexnum; i++)
	{
		int res = bfs(i);
		if (res != 0)
		{
			buffer.seekp(-1, ios::cur);
			buffer << "}";

			if (remain -= res)
				buffer << "{";
			else
				buffer << endl;
		}
	}
	cout << buffer.str();

	for (int i = 0; i < g1.vexnum; i++)
	{
		ArcNode* cur = g1.vertices[i].firstarc;
		while (cur != nullptr)
		{
			ArcNode* mid = cur->nextarc;
			delete cur;
			cur = mid;
		}
	}


	return 0;
}