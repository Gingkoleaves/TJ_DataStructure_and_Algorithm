// DAG有向无环图的最长路径（点权而非边权），和各点到叶的最长距离
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define VertexType unsigned int
#define MAX_VERTEX_NUM 2000
using namespace std;



typedef struct ArcNode {
	// int weight;//边的权值
	int adjvex;  //该弧所指向的顶点的位置,链接表中对应元素的的下标
	struct ArcNode* nextarc;//指向下一条弧的指针
}ArcNode;  //边结点类型

typedef struct VNode {
	VertexType data;
	int cost;
	int sta = 0;//表示是否被访问过/被访问中,1已经访问，0未访问，-1正在访问
	//顶点信息
	ArcNode* firstarc = nullptr; //指向第一条依附该顶点的指针
	ArcNode* lastarc = nullptr;

	void push(ArcNode* newptr)
	{
		if (firstarc == nullptr)
		{
			firstarc = newptr;
			lastarc = firstarc;
		}
		else
		{
			ArcNode* mid = lastarc;
			lastarc = newptr;
			mid->nextarc = lastarc;
		}
	}

}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;  //邻接表
	int vexnum, arcnum;
}ALGraph;

ALGraph G1;
int total_consume[MAX_VERTEX_NUM];//使用与vertice相同的下标-值对应
int is_max[MAX_VERTEX_NUM];

int LocateVex(const ALGraph& g1, VertexType d1)
{
	for (int i = 0; i < g1.vexnum; i++)
		//仅限非char*
		if (g1.vertices[i].data == d1)
			return i;

	return g1.vexnum;
}

//从i1下标开始dfs,返回-1表示出现问题
int dfs(ALGraph& g1,int* total_consumes ,int i1)
{
	g1.vertices[i1].sta = -1;
	int count = 0;
	//vector<int> max_index;
	//if((g1.vertices[i1]).firstarc!=nullptr)
	//	max_index.push_back(((g1.vertices[i1]).firstarc)->adjvex);

	ArcNode* cur_arc = g1.vertices[i1].firstarc;
	while (cur_arc != nullptr)
	{
		int state = g1.vertices[cur_arc->adjvex].sta;
		if (state == -1)return -1;
		else if (state == 0)
		{
			int mid=dfs(g1, total_consumes, cur_arc->adjvex);
			if (mid == -1)return -1;

			if (mid > count)
			{
				count = mid;
				// max_index.clear();
				// max_index.push_back( cur_arc->adjvex);
			}
			//else if (mid == count)
			//{
			//	max_index.push_back(cur_arc->adjvex);
			//}
			// count = mid > count ? mid : count;//更新为最长子路
		}
		else
		{
			if (total_consumes[cur_arc->adjvex] > count)
			{
				count = total_consumes[cur_arc->adjvex];
				// max_index.clear();
				// max_index.push_back(cur_arc->adjvex);
			}
			//else if (total_consumes[cur_arc->adjvex] == count)
			//{
			//	// max_index.push_back(cur_arc->adjvex);
			//}
			//count = total_consumes[cur_arc->adjvex] > count ? total_consumes[cur_arc->adjvex] : count;//更新为最长子路
		}

		cur_arc = cur_arc->nextarc;
	}

	g1.vertices[i1].sta = 1;
	total_consumes[i1] = count + g1.vertices[i1].cost;

	//for(int i:max_index)
	//	g1.vertices[i].is_max = 1;//标记最大子树们

	// cout << g1.vertices[i1].data;//打印数据
	return total_consumes[i1];
}

bool topo_sort(ALGraph& g1)
{
	for (int i = 0; i < g1.vexnum; i++)
	{
		if (g1.vertices[i].sta == 0)
			if (dfs(g1, total_consume,i)==-1)return false;
	}

	return true;
}

void clear(queue<int>& q) {
	queue<int> empty;
	swap(empty, q);
}

// 课程编号从1开始，不妨视为邻接表的下标
// 不妨把向视为从高优先级指向低优先级
int main()
{
	int n;
	cin >> n;
	//初始化链表
	for (int i = 0; i < n; i++)
		G1.vertices[i].data = i + 1;

	memset(is_max, 0, sizeof(is_max));
	memset(total_consume, 0, sizeof(total_consume));

	G1.vexnum = n;
	G1.arcnum = 0;

	for (int i = 0; i < n; i++)
	{
		int weight, k;
		cin >> weight >> k;
		G1.vertices[LocateVex(G1, i + 1)].cost = weight;
		G1.arcnum += k;

		for (int j = 0; j < k; j++)
		{
			int code;
			cin >> code;

			ArcNode* NewArc = new ArcNode;
			NewArc->adjvex = LocateVex(G1, code);
			NewArc->nextarc = nullptr;

			G1.vertices[LocateVex(G1, i+1)].push(NewArc);
		}
	}

	//找最长路:dp刷表
	topo_sort(G1);//找出每门课最短所需时间


	//还需标记最大耗时的课is_max
	//先找最长路终点，再遍历邻接表找次级最大，复杂度共n

	queue<int> max_index;
	max_index.push(0);
	for (int i = 0; i < n; i++)
	{
		if (total_consume[max_index.front()] < total_consume[i])
		{
			clear(max_index);
			memset(is_max, 0, sizeof(is_max));

			max_index.push(i);
			is_max[i] = 1;
		}
		else if (total_consume[max_index.front()] == total_consume[i])
		{
			max_index.push(i);
			is_max[i] = 1;
		}
	}

	//把max_index中值置is_max=1

	while(!max_index.empty())
	{
		int i = max_index.front();
		max_index.pop();

		ArcNode* cur_arc = G1.vertices[i].firstarc;
		while (cur_arc != nullptr)
		{
			if (total_consume[cur_arc->adjvex] == total_consume[i] - G1.vertices[i].cost)
			{
				is_max[cur_arc->adjvex] = 1;
				max_index.push(cur_arc->adjvex);
			}

			cur_arc = cur_arc->nextarc;
		}
	}

	for (int i = 0; i < n; i++)
		cout << total_consume[i] << ' ' << is_max[i] << endl;


	return 0;
}