//根据邻接表查找最小生成树
#include <iostream>
#include <iomanip>

#define VertexType unsigned int
#define MAX_VERTEX_NUM 100
using namespace std;

//采用Prim算法，取第一个点开始
typedef int VRType;

struct {
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];//辅助表

//定义一个邻接矩阵
typedef struct {
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	VertexType vexs[MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;
MGraph G1;


int LocateVex(int vex)
{
	return vex - 1;
}

//u为选定的顶点
void MiniSpanTree_PRIM(const MGraph& G, VertexType u)
{
	int count = 0;
	int k, j, i, minCost;
	k = LocateVex(u);//表示从节点自身信息到其索引的转换
	//初始化辅助表
	for (j = 0; j < G.vexnum; ++j)
		if (j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j];
		}
	closedge[k].adjvex = u;
	closedge[k].lowcost = -1;

	//遍历 边数-1次
	for (i = 0; i < G.vexnum-1; ++i)
	{ // k=minimum(closedge);
		minCost = 10000000;
		for (j = 0; j < G.vexnum; ++j)
		{
			if (closedge[j].lowcost < minCost &&
				closedge[j].lowcost != -1)
			{
				minCost = closedge[j].lowcost;
				k = j;
			}
		}
		//printf("(%d,%d)\n", closedge[k].adjvex, G.vexs[k]);
		count += G1.arcs[k][LocateVex(closedge[k].adjvex)];
		//把选定的点加入点集
		closedge[k].lowcost = -1;
		//更新closedge辅助表
		for (j = 0; j < G.vexnum; ++j)
			if (G.arcs[k][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j];
			}
	}

	cout << count<<endl;
}

//由于0是可能出现的，所以用-1表示已经在点集中
int main()
{
	int vexnum;
	cin >> vexnum;

	G1.arcnum = vexnum * vexnum;
	G1.vexnum = vexnum;
	for (int i = 0; i < vexnum; i++)
		G1.vexs[i] = i + 1;
	
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
		{
			cin >> G1.arcs[i][j];
			G1.arcs[j][i] = G1.arcs[i][j];
		}	

	int already_done;
	cin >> already_done;

	int src, dst;
	for (int i = 0; i < already_done; i++)
	{
		cin >> src >> dst;
		G1.arcs[LocateVex(src)][LocateVex(dst)] = 0;
		G1.arcs[LocateVex(dst)][LocateVex(src)] = 0;
	}

	MiniSpanTree_PRIM(G1, 1);
	return 0;
}
