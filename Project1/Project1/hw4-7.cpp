//给出指定图的欧拉回路数量
//递归减小图，给出不断减小的图的欧拉回路


//方法1：遍历所有路
#include <iostream>
#include <cstring>
#include <cmath>
#define VertexType unsigned int
#define MAX_VERTEX_NUM 5
using namespace std;

typedef struct {
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;
MGraph G1;

int visit[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };

//输入编号，返回下标
inline int LocateVex(int vex)
{
	return vex - 1;
}

// point是端点编号,seq中元素也都是编号
void dfs(int route_depth, int* seq, int seq_length,int point)
{
	if (route_depth >= 8)
	{
		for (int i = 0; i < 9; i++)
			cout << seq[i];
		cout << endl;
	}

	for (int i = 1; i <= 5; i++)
	{
		if (i == point)continue;
		if (!visit[LocateVex(point)][LocateVex(i)]&&G1.arcs[LocateVex(point)][LocateVex(i)])
		{
			seq[seq_length+1] = i;
			visit[LocateVex(point)][LocateVex(i)] = 1;
			visit[LocateVex(i)][LocateVex(point)] = 1;
			dfs(route_depth + 1, seq, seq_length + 1, i);
			visit[LocateVex(point)][LocateVex(i)] = 0;
			visit[LocateVex(i)][LocateVex(point)] = 0;
		}
	}
}


int main()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			G1.arcs[i][j] = 1;

	for (int i = 0; i < 5; i++)
		G1.arcs[i][i] = 0;

	G1.arcs[LocateVex(1)][LocateVex(4)] = 0;
	G1.arcs[LocateVex(4)][LocateVex(1)] = 0;
	G1.arcs[LocateVex(2)][LocateVex(4)] = 0;
	G1.arcs[LocateVex(4)][LocateVex(2)] = 0;

	int seq[10];
	seq[0] = 1;
	dfs(0, seq, 0, 1);

	return 0;
}