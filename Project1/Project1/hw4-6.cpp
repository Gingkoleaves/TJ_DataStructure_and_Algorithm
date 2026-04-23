//小马吃草
//弗洛伊德算法，求最短路

#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
#define VertexType unsigned int
#define MAX_VERTEX_NUM 1200
using namespace std;

typedef struct {
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;
MGraph G1;

//输入编号，返回下标
inline int LocateVex(int vex)
{
	return vex - 1;
}

void Floyd(int vexnum)
{
	for (int k = 0; k < vexnum; k++)
	{
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
			{
				if (G1.arcs[i][k] != -1 && G1.arcs[k][j] != -1)
					if (G1.arcs[i][j] == -1)
						G1.arcs[i][j] = (G1.arcs[i][k]) + (G1.arcs[k][j]);
					else
						G1.arcs[i][j] = min((G1.arcs[i][j]), (G1.arcs[i][k]) + (G1.arcs[k][j]));


			}
	}
}


/*
void Floyd(int vexnum, int top_vex)
{
	if (top_vex > 0)
		Floyd(vexnum, top_vex - 1);

	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
		{
			if (G1.arcs[i][top_vex] != -1 && G1.arcs[top_vex][j] != -1)
				if (G1.arcs[i][j] == -1)
					G1.arcs[i][j] = (G1.arcs[i][top_vex]) + (G1.arcs[top_vex][j]);
				else
					G1.arcs[i][j] = min((G1.arcs[i][j]), (G1.arcs[i][top_vex]) + (G1.arcs[top_vex][j]));
		}
}*/

int grass[MAX_VERTEX_NUM];
//点的编号从1开始
int main()
{
	// -1表示正无穷
	memset(grass, 0, sizeof(int) * MAX_VERTEX_NUM);
	memset(G1.arcs, -1, sizeof(int) * MAX_VERTEX_NUM * MAX_VERTEX_NUM);

	cin >> G1.vexnum >> G1.arcnum;
	//for (int i = 0; i < G1.vexnum; i++)
	//{
	//	for(int j=0;j < G1.vexnum;j++)
	//		G1.arcs[i][j] = -1;
	//}

	//错误原因：没有考虑两个点间有多条路的情况（即i->j有多条路）
	//for (int i = 0; i < G1.arcnum; i++)
	//{
	//	int src_name, dst_name, weight;
	//	cin >> src_name >> dst_name>> weight;

	//	G1.arcs[LocateVex(src_name)][LocateVex(dst_name)] = weight;
	//	G1.arcs[LocateVex(dst_name)][LocateVex(src_name)] = weight;
	//}

	for (int i = 0; i < G1.arcnum; i++) {
		int src_name, dst_name, weight;
		cin >> src_name >> dst_name >> weight;

		if (G1.arcs[src_name - 1][dst_name - 1] == -1 || G1.arcs[src_name - 1][dst_name - 1] > weight) {
			G1.arcs[src_name - 1][dst_name - 1] = weight;
		}
		if (G1.arcs[dst_name - 1][src_name - 1] == -1 || G1.arcs[dst_name - 1][src_name - 1] > weight) {
			G1.arcs[dst_name - 1][src_name - 1] = weight;
		}
	}

	for (int i = 0; i < G1.vexnum; i++)
	{
		G1.arcs[i][i] = 0;
	}
	
	int G, H;//草数和马数
	cin >> G >> H;

	for (int i = 0; i < G; i++)
	{
		int grass_pos;
		cin >> grass_pos;
		grass[(grass_pos-1)] = 1;
	}

	Floyd(G1.vexnum);

	for (int i = 0; i < H; i++)
	{
		int src, dst;
		cin >> src >> dst;
		int min_cost = 1000000;//一个大数
		// cout << G1.arcs[LocateVex(src)][LocateVex(dst)] << endl;
		for (int j = 0; j < G1.vexnum; j++)
		{
			if (!grass[j])continue;
			if (G1.arcs[(src-1)][j] != -1 && G1.arcs[j][(dst-1)] != -1)
					min_cost = min(min_cost, (G1.arcs[(src-1)][j]) + (G1.arcs[j][(dst-1)]));
		}
		cout << min_cost << endl;
	}

	return 0;
}

//#include <iostream>
//#include <cstring>
//#include <limits>
//#define VertexType unsigned int
//#define MAX_VERTEX_NUM 1000
//using namespace std;
//
//typedef struct {
//    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//    VertexType vexs[MAX_VERTEX_NUM];
//    int vexnum, arcnum;
//} MGraph;
//MGraph G1;
//
//inline int LocateVex(int vex) {
//    return vex - 1;
//}
//
//void Floyd(int vexnum) {
//    for (int k = 0; k < vexnum; k++) {
//        for (int i = 0; i < vexnum; i++) {
//            for (int j = 0; j < vexnum; j++) {
//                if (G1.arcs[i][k] != -1 && G1.arcs[k][j] != -1) {
//                    int temp = G1.arcs[i][k] + G1.arcs[k][j];
//                    if (G1.arcs[i][j] == -1 || G1.arcs[i][j] > temp) {
//                        G1.arcs[i][j] = temp;
//                    }
//                }
//            }
//        }
//    }
//}
//
//int grass[MAX_VERTEX_NUM];
//
//int main() {
//    memset(grass, 0, sizeof(int) * MAX_VERTEX_NUM);
//
//    cin >> G1.vexnum >> G1.arcnum;
//    for (int i = 0; i < G1.vexnum; i++) {
//        for (int j = 0; j < G1.vexnum; j++) {
//            G1.arcs[i][j] = -1;
//        }
//        G1.vexs[i] = i + 1; // Assuming vertices are numbered from 1 to vexnum
//    }
//
//    for (int i = 0; i < G1.arcnum; i++) {
//        int src_name, dst_name, weight;
//        cin >> src_name >> dst_name >> weight;
//        int src = LocateVex(src_name);
//        int dst = LocateVex(dst_name);
//        if (src >= 0 && src < G1.vexnum && dst >= 0 && dst < G1.vexnum) {
//            if (G1.arcs[src][dst] == -1 || G1.arcs[src][dst] > weight) {
//                G1.arcs[src][dst] = weight;
//            }
//            if (G1.arcs[dst][src] == -1 || G1.arcs[dst][src] > weight) {
//                G1.arcs[dst][src] = weight;
//            }
//        }
//    }
//
//    for (int i = 0; i < G1.vexnum; i++) {
//        G1.arcs[i][i] = 0;
//    }
//
//    int G, H;
//    cin >> G >> H;
//
//    for (int i = 0; i < G; i++) {
//        int grass_pos;
//        cin >> grass_pos;
//        int idx = LocateVex(grass_pos);
//        if (idx >= 0 && idx < G1.vexnum) {
//            grass[idx] = 1;
//        }
//    }
//
//    Floyd(G1.vexnum);
//
//    for (int i = 0; i < H; i++) {
//        int src, dst;
//        cin >> src >> dst;
//        int src_idx = LocateVex(src);
//        int dst_idx = LocateVex(dst);
//        if (src_idx < 0 || src_idx >= G1.vexnum || dst_idx < 0 || dst_idx >= G1.vexnum) {
//            cout << -1 << endl;
//            continue;
//        }
//        int min_cost = numeric_limits<int>::max();
//        for (int j = 0; j < G1.vexnum; j++) {
//            if (grass[j]) {
//                if (G1.arcs[src_idx][j] != -1 && G1.arcs[j][dst_idx] != -1) {
//                    int cost = G1.arcs[src_idx][j] + G1.arcs[j][dst_idx];
//                    if (cost < min_cost) {
//                        min_cost = cost;
//                    }
//                }
//            }
//        }
//        if (min_cost == numeric_limits<int>::max()) {
//            cout << -1 << endl;
//        }
//        else {
//            cout << min_cost << endl;
//        }
//    }
//
//    return 0;
//}