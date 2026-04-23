#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

struct Node {
	int parent = -1;
	int lchild = -1;
	int rchild = -1;
	short flag = 0;
};

Node list[100500];
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

int main()
{
	//读入树（存储边，从a->b和b->a）
	My_Queue<int> CurLevel;

	
	int LevelSize = 1;//当前层的size
	CurLevel.push(0);

	int num,SrcNum;
	scanf("%d %d", &num,&SrcNum);

	//for (int i=1;i<num*2+1;i+=2)
	//{
	//	int cnt = 0;
	//	for (int j = 0; j < LevelSize;j++)
	//	{
	//		int head=CurLevel.front();
	//		CurLevel.pop();

	//		scanf("%d", &list[head].lchild);
	//		scanf("%d", &list[head].rchild);
	//		
	//		if (list[head].lchild != -1)
	//		{
	//			CurLevel.push(list[head].lchild);
	//			list[list[head].lchild].parent = head;
	//			cnt++;
	//		}
	//		if (list[head].rchild != -1)
	//		{
	//			CurLevel.push(list[head].rchild);
	//			list[list[head].rchild].parent = head;
	//			cnt++;
	//		}
	//		if (j >= LevelSize)
	//			break;
	//	}
	//	LevelSize = cnt;
	//}


	for (int i = 0; i < num; i++)
	{
		scanf("%d", &list[i].lchild);
		scanf("%d", &list[i].rchild);
		if(list[i].lchild != -1)
			list[list[i].lchild].parent = i;
		if (list[i].rchild != -1)
			list[list[i].rchild].parent = i;
	}

	int mins = 0;
	int cnt = 1;
	int JustInfected = 1;

	My_Queue<int> q1;
	q1.push(SrcNum);
	list[SrcNum].flag = 1;

	while (cnt < num)
	{
		int CurInfect = 0;
		for (int i = 0; i < JustInfected; i++)
		{
			int infect = q1.front();
			q1.pop();
			

			if (list[infect].lchild != -1 && list[list[infect].lchild].flag == 0)
			{ 
				q1.push(list[infect].lchild);
				CurInfect++; 
				list[list[infect].lchild].flag = 1;
			}

			if (list[infect].rchild != -1 && list[list[infect].rchild].flag == 0)
			{
				q1.push(list[infect].rchild); 
				CurInfect++; 
				list[list[infect].rchild].flag = 1;
			}

			if (list[infect].parent != -1 && list[list[infect].parent].flag == 0)
			{
				q1.push(list[infect].parent); 
				CurInfect++; 
				list[list[infect].parent].flag = 1;
			}
		}

		JustInfected = CurInfect;
		mins++;
		cnt += JustInfected;
	}

	printf("%d", mins);



	return 0;
}

// 818
// 817
// 815 819
// 814 816 820
// 30
// 29 31
// 28 821 32 809
// 27 822 33 807 810 811
//