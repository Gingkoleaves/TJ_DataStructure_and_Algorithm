#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
#define N 1000
#define N4 4000

int matrix[N][N];
int matrix2[N][N];
int seq[N4];
int m, n;//m行n列



template<typename T>
struct My_Queue {

	struct Node {
		T elem;
		Node* next;
	};

	Node* _front;
	Node* _back;

	My_Queue()
	{
		_front = new Node;//头结点
		_back = _front;
		_back->next = NULL;
	}
	~My_Queue()
	{
		while (_back != _front)
		{
			Node* mid = _front->next;
			delete _front;
			_front = mid;
		}
	}

	bool empty()
	{
		if (_front == _back)
			return true;
		return false;
	}

	T front()
	{
		return _front->next->elem;
	}

	void pop()
	{
		if (_front != _back)
		{
			Node* new_front = _front->next->next;
			if (_front->next == _back)
				_back = _front;
			delete _front->next;
			_front->next = new_front;
		}
	}

	void push(T new_elem)
	{
		Node* new_node = new Node;
		new_node->elem = new_elem;
		new_node->next = NULL;
		_back->next = new_node;
		_back = new_node;
	}
};


//相邻的1置零,返回连通块数量
int bfs_for_connected_1(My_Queue<int> &q1, int(&matrix)[N][N])
{
	int cnt = 0;
	while (!q1.empty())
	{
		int pos_num = q1.front();
		q1.pop();

		//越界
		if (pos_num < 0 || pos_num >= m * n)
			continue;

		cnt++;

		int col = pos_num % n;
		int row = pos_num / n;

		matrix[row][col] = 0;
		if (row + 1 >= 0 && row + 1 < m && matrix[row + 1][col] == 1)q1.push(pos_num + n);
		if (row - 1 >= 0 && row - 1 < m && matrix[row - 1][col] == 1)q1.push(pos_num - n);
		if (col + 1 >= 0 && col + 1 < n && matrix[row][col + 1] == 1)q1.push(pos_num + 1);
		if (col - 1 >= 0 && col - 1 < n && matrix[row][col - 1] == 1)q1.push(pos_num - 1);

	}
	return cnt;
}
//第一版草稿先用最可靠的结构，后续再简化




int main()
{
	scanf("%d%d", &m, &n);//m行n列
	My_Queue<int> q1;
	int cnt_all = 0;

	for(int i=0;i<m;i++)
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &matrix[i][j]);
			matrix2[i][j] = matrix[i][j];
		}

	//所有连通块
	for (int i = 0; i < m * n; i++)
	{
		if (matrix[i / n][i % n] == 0)
			continue;
		else
		{
			q1.push(i);
			bfs_for_connected_1(q1,matrix);
			cnt_all++;
		}
	}
	
	//完全在边缘中的连通快数量
	int ptr = 0;
	//顺时针边缘序号集
	for (int i = 0; i < n-1;ptr++, i++)
	{
		seq[ptr] = i;
	}
	for (int i = n - 1; i < n * m-1; ptr++, i += n)
	{
		seq[ptr] = i;
	}	
	for (int i = n * m - 1; i > n * (m - 1); ptr++, i--)
	{
		seq[ptr] = i;
	}
	for (int i = n * (m - 1); i > 0; ptr++, i-=n)
	{
		seq[ptr] = i;
	}


	//先检查0,0处是否有连通块
	if (matrix2[0][0] == 1)
	{
		q1.push(0);
		int cnt_for_0 = 0;

		for (int i = 0; matrix2[0][i] == 1; i++, cnt_for_0++);
		for (int j = 1; matrix2[j][0] == 1; j++, cnt_for_0++);

		int num_0 = bfs_for_connected_1(q1, matrix2);
		if (num_0 == cnt_for_0)
			cnt_all--;
	}

	for (int i = 0; i < ptr; i++)
	{
		if (matrix2[seq[i]/n][seq[i] % n] == 0)
			continue;
		else//等于1
		{
			int start = i;
			while (i <= ptr && matrix2[seq[i] / n][seq[i] % n] == 1)i++;
			int length = i - start;

			q1.push(seq[i-1]);
			int connects=bfs_for_connected_1(q1, matrix2);

			if (connects == length)
				cnt_all--;
		}
	}







	//一直读取直到遇到1
	//遇到1后，一直读取直到遇到0，记录连续的1的个数
	//从末位1开始，查找连通快，返回连通块的个数
	//比较两个值，如果相等，则是一个完全在边缘的连通块



	/*
	//边缘连通块
	int cnt_edge = 0;
	for (int i = 0; i < n; i++)
	{
		if (matrix2[i / m][i % m] == 0)
			continue;
		else
		{
			q1.push(i);
			bfs_for_connected_1(q1,matrix2);
			cnt_edge++;
		}
	}
	for (int i = 0; i <n*m; i+=n)
	{
		if (matrix2[i / m][i % m] == 0)
			continue;
		else
		{
			q1.push(i);
			bfs_for_connected_1(q1, matrix2);
			cnt_edge++;
		}
	}
	for (int i = n*(m-1); i < n * m; i ++)
	{
		if (matrix2[i / m][i % m] == 0)
			continue;
		else
		{
			q1.push(i);
			bfs_for_connected_1(q1, matrix2);
			cnt_edge++;
		}
	}
	for (int i = n-1; i < n * m; i += n)
	{
		if (matrix2[i / m][i % m] == 0)
			continue;
		else
		{
			q1.push(i);
			bfs_for_connected_1(q1, matrix2);
			cnt_edge++;
		}
	}
	*/

	printf("%d", cnt_all);

	return 0;
}