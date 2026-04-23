#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

#define OK 0
#define N 100500

template<typename T>
struct MyStack {

	T* bottom;
	T* top_one;
	int max_len = N;

public:
	MyStack()
	{
		bottom = new T[max_len];
		top_one = bottom;
	}
	~MyStack()
	{
		delete[] bottom;
	}

	int push(T obj)
	{
		if (top_one - bottom == max_len)//满了
		{
			max_len *= 2;
			T* mid = new T[max_len];
			memcpy(mid, bottom, sizeof(T) * (max_len / 2));
			delete[] bottom;

			bottom = mid;
			top_one = bottom + max_len/2;
		}
		*top_one++ = obj;

		return OK;
	}

	bool empty()
	{
		if (top_one == bottom)
			return true;
		else return false;
	}

	T pop()
	{
		if (top_one == bottom)
			throw runtime_error("Stack is empty!");
		return *(--top_one);
	}

	T top()
	{
		if (top_one == bottom)
			throw runtime_error("Stack is empty!");
		return *(top_one - 1);
	}
};

char inp[N];
int main()
{
	cin.getline(inp, N);
	int len = strlen(inp);

	int max_len = -1;
	char* max_len_pos = NULL;

	char* cur_ptr = inp;
	while (1)
	{
		if (cur_ptr >= inp + len)
			break;

		stack<char> test;
		while (*cur_ptr != '('&& *cur_ptr != '\0')
			cur_ptr++;

		if (*cur_ptr == '\0')
			break;

		char* start_ptr = cur_ptr;

		test.push(*cur_ptr++);
		int cur_max_len = -1;
		int cur_len = 1;

		int ok = 1;
		while (*cur_ptr != '\0')
		{
			if (*cur_ptr == ')' && !test.empty() && test.top() == '(')
			{
				test.pop();
				cur_len++;
			}
			else
			{
				test.push(*cur_ptr);
				cur_len++;
			}

			cur_ptr++;

			if (test.empty())
			{
				cur_max_len = cur_len;
			}
		}

		if (max_len < cur_max_len)
		{
			max_len = cur_max_len;
			max_len_pos = start_ptr;
		}

		if (cur_max_len > 0)
			cur_ptr = start_ptr + cur_max_len;
		else
			cur_ptr = start_ptr + 1;
	}

	if (max_len == -1)
	{
		max_len = 0;
		max_len_pos = inp;
	}


	printf("%d %d\n", max_len, max_len_pos - inp);

	return 0;
}
//只用确定头尾
//栈存储括号位置，从而在每次匹配时计算匹配的两个括号的距离
