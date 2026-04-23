// 由于已知存在唯一解
// 可以证明，对于所有元素，必须给出全排序（纵横均需要）

// 拓扑排序：课本ppt给出的topo程序，复杂度太高O(n3)
// 使用O(n+e)的排序方法：dfs
#include <iostream>
#include <stack>
#define VertexType unsigned int
#define MAX_VERTEX_NUM 2000
using namespace std;

typedef struct ArcNode {
	int adjvex;  //该弧所指向的顶点的位置,链接表中对应元素的的下标
	struct ArcNode* nextarc;//指向下一条弧的指针
}ArcNode;  //边结点类型

typedef struct VNode {
	VertexType data;
	int sta=0;//表示是否被访问过/被访问中,1已经访问，0未访问，-1正在访问
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
ALGraph G2;

int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
stack<VertexType> s1;
int col[MAX_VERTEX_NUM];
int row[MAX_VERTEX_NUM];

int LocateVex(const ALGraph& g1,VertexType d1)
{
	for (int i = 0; i < g1.vexnum; i++)
		//仅限非char*
		if (g1.vertices[i].data == d1)
			return i;
	
	return g1.vexnum;
}

//从下标为i1的节点开始dfs打印拓扑排序
//从拓扑排序小端输出到大端
bool dfs(ALGraph& g1,int i1)
{
	g1.vertices[i1].sta = -1;

	ArcNode* cur_arc = g1.vertices[i1].firstarc;
	while (cur_arc != nullptr)
	{
		int state = g1.vertices[cur_arc->adjvex].sta;
		if (state == -1)return false;
		else if (state==0)
			if(!dfs(g1, cur_arc->adjvex))return false;
		else;

		cur_arc = cur_arc->nextarc;
	}

	g1.vertices[i1].sta = 1;
	// cout << g1.vertices[i1].data;//打印数据
	s1.push(g1.vertices[i1].data);
	return true;
}


bool topo_sort(ALGraph& g1)
{
	for (int i = 0; i < g1.vexnum; i++)
	{
		if (g1.vertices[i].sta == 0)
			if (!dfs(g1, i))return false;
	}

	return true;
}

int main()
{
	int k, n, m;
	cin >> k >> n >> m;

	G1.vexnum = k;
	G2.vexnum = k;
	G1.arcnum = k - 1;
	G2.arcnum = k - 1;

	for (int i = 0; i < k; i++)
	{
		G1.vertices[i].data = i + 1;
		G2.vertices[i].data = i + 1;
	}


	//纵向拓扑排序
	for (int i = 0; i < n; i++)
	{
		int src_elem, dst_elem;
		cin >> src_elem >> dst_elem;//above->below

		ArcNode* NewArc = new ArcNode;
		NewArc->adjvex = LocateVex(G1, dst_elem);
		NewArc->nextarc = nullptr;

		G1.vertices[LocateVex(G1, src_elem)].push(NewArc);
	}

	//横向排序
	for (int i = 0; i < m; i++)
	{
		int src_elem, dst_elem;
		cin >> src_elem >> dst_elem;//left->right

		ArcNode* NewArc = new ArcNode;
		NewArc->adjvex = LocateVex(G2, dst_elem);
		NewArc->nextarc = nullptr;

		G2.vertices[LocateVex(G2, src_elem)].push(NewArc);
	}
	bool flag = true;

	flag = topo_sort(G1) ? flag : false;
	for (int i = 0; !s1.empty(); i++)
	{
		col[i] = s1.top();
		s1.pop();
	}

	// cout << endl;

	flag = topo_sort(G2) ? flag : false;
	for (int i = 0; !s1.empty(); i++)
	{
		row[i] = s1.top();
		s1.pop();
	}
	// cout << endl;

	if (flag)
	{
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (col[i] == row[j])cout << col[i] << ' ';
				else cout << 0 << ' ';
			}
			cout << endl;
		}
	}
	else
		cout << -1 << endl;
	return 0;
}