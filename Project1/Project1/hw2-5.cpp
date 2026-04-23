#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>


using namespace std;

const int MIN = numeric_limits<int>::min();

//用坐标表表示，从而用数值计算代替指针计算
template<typename T>
struct My_Queue {

	T* Mem_Beginer;
	T* Mem_Ending;
	int Mem_MaxLen;
	T* _front;
	T* _back;
	
	//要用头结点表示空队列
	My_Queue(int iMaxLen)
	{
		Mem_Beginer = new T[iMaxLen+1];
		Mem_Ending = Mem_Beginer + iMaxLen;
		Mem_MaxLen = iMaxLen;

		_front = Mem_Beginer;
		_back = Mem_Beginer;
	}
	~My_Queue()
	{
		delete Mem_Beginer;
	}

	bool empty()
	{
		if (_front == _back)
			return true;
		return false;
	}

	T front()
	{
		return _front;
	}

	void pop()
	{
		if (_front != _back)
		{
			T* targ;
			if (_front == Mem_Ending)
			{
				targ = Mem_Beginer;
				_front = Mem_Beginer;
			}
			else
			{
				targ = _front + 1;
				_front = _front + 1;
			}

			printf("%d\n", *targ);
		}
		else
		{
			printf("Queue is Empty\n");
		}

	}

	void push(T new_elem)
	{
		if (_front - _back == 1 || _back - _front == Mem_MaxLen)
			printf("Queue is Full\n");
		else
		{
			if (_back == Mem_Ending)
			{
				*Mem_Beginer = new_elem;
				_back = Mem_Beginer;
			}
			else
			{
				*(_back + 1) = new_elem;
				_back = _back + 1;
			}
		}
	}

	T* next(T* ptr)
	{
		if (ptr == Mem_Ending)
			return Mem_Beginer;
		else
			return ptr + 1;
	}

	void getMax()
	{
		if (empty())
			printf("Queue is Empty\n");
		else
		{
			T* cur_ptr = next(_front);
			T* End_next = next(_back);
			int max = MIN;
			while (cur_ptr != End_next)
			{
				if (*cur_ptr > max)
					max = *cur_ptr;

				cur_ptr = next(cur_ptr);
			}
			
			printf("%d\n", max);
		}
		
	}

	void Quit()
	{
		T* cur_ptr = next(_front);
		T* End_next = next(_back);
		int max = MIN;
		while (cur_ptr != End_next)
		{
			printf("%d ", *cur_ptr);

			cur_ptr = next(cur_ptr);
		}
		printf("\n");
	}
};



int main()
{
	int n;
	scanf("%d", &n);
	My_Queue<int> q1(n);
	char cmd[100];

	int ok = 1;
	while (cin.getline(cmd,100))
	{
		switch (cmd[0])
		{
		case('q'):
			ok = 0;
			q1.Quit();
			break;
		case('m'):
			q1.getMax();
			break;
		case('e'):
			int n;
			char cmd2[100];
			sscanf(cmd, "%s%d", &cmd2, &n);
			q1.push(n);
			break;
		case('d'):
			q1.pop();
			break;
		default:
			break;

		}
		if (!ok)
			break;
	}
	return 0;
}