#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

#define OK 0


template<typename T>
struct MyStack {
	T* bottom;
	T* top_one;
	int max_len=10;

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
			memcpy(mid, bottom,sizeof(T)*(max_len/2));
			delete[] bottom;

			bottom = mid;
			top_one = bottom + max_len;
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
		return *(top_one -1);
	}
};


int main()
{
	MyStack<char> input;

	char inp[100];
	cin.getline(inp, 100);
	for (int i = strlen(inp)-1; i>=0; i--)
	{
		input.push(inp[i]);
	}


	while (cin.getline(inp, 100))
	{
		MyStack<char> input_r=input;
		MyStack<char> answer;
		MyStack <char>station;

		for (int i = strlen(inp)-1; i >= 0; i--)
		{
			answer.push(inp[i]);
		}

		while (1)
		{
			if (!input_r.empty() && answer.top() == input_r.top())
			{
				answer.pop();
				input_r.pop();
			}
			else if (!station.empty() && station.top() == answer.top())
			{
				station.pop();
				answer.pop();
			}//station非空且answer顶！=station顶时，如果inp非空，什么都不做，如果inp空，no
			else if (!input_r.empty() && answer.top() != input_r.top())
			{
				station.push(input_r.top());
				input_r.pop();
			}
			//此后input_r为空
			else if (input_r.empty() && !station.empty() && station.top() == answer.top())
			{
				station.pop();
				input_r.pop();
			}
			else if (input_r.empty() && !station.empty() && station.top() != answer.top())
			{
				cout << "no" << endl;
				break;
			}
			else if (input_r.empty() && station.empty())
			{
				cout << "yes" << endl;
				break;
			}
		}
	}

	return 0;
}