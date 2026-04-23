#include <iostream>
#include <cstring>



using namespace std;
#define OK 0
#define N 100
#define A 20
#define MAX_LEN 1000

const char NOT = '!';
const char  AND = '&';
const char  OR = '|';
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
	int size()
	{
		return top_one - bottom;
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
			top_one = bottom + max_len / 2;
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
		if (top_one != bottom)
			return *(--top_one);
		throw runtime_error("Stack is empty!");
	}

	T top()
	{
		if (top_one != bottom)
			return *(top_one - 1);
		throw runtime_error("Stack is empty!");
	}

	void clear()
	{
		bottom = new T[max_len];
		top_one = bottom;
	}
};

MyStack<char> operators;
MyStack<char> values;

void Switch(char& c1)
{
	if (c1 == 'V')
		c1 = 'F';
	else if (c1 == 'F')
		c1 = 'V';
	else return;
}

//void Operate_by_operator(MyStack<char>(*operators), MyStack<char>(*values), char operator1)
void Operate_by_operator(char operator1,MyStack<char>* values,MyStack<char>* operators)
{
	char op1,op2;	
	if (operator1 == ')')
	{
		if (operators->top() != '(')
		{
			Operate_by_operator(operators->pop(),values, operators);
			operators->push(')');
		}
		else
			operators->pop();
	}
	else if (operator1 == NOT)
	{
		op1 = values->pop();
		Switch(op1);
		values->push(op1);
	}
	else if (operator1 == AND)
	{
		op1 = values->pop();
		op2 = values->pop();
		
		values->push((op1 == 'V' && op2 == 'V')?'V':'F');
	}
	else if (operator1 == OR)
	{
		op1 = values->pop();
		op2 = values->pop();

		values->push((op1 == 'V' || op2 == 'V') ? 'V' : 'F');
	}

}

//返回前者大于后者的bool值,后者在前者的右侧
bool cmp_priority(char c1, char c2)
{
	switch (c1)
	{
	case('('):
		c1 = -1;
		break;
	case(')'):
		c1 = 10;
		break;
	case('!'):
		c1 = 3;
		break;
	case('&'):
		c1 = 2;
		break;
	case('|'):
		c1 = 1;
		break;
	default:
		break;
	}

	switch (c2)
	{
	case('('):
		c2 = 10;
		break;
	case(')'):
		c2 = -1;
		break;
	case('!'):
		c2 = 3;
		break;
	case('&'):
		c2 = 2;
		break;
	case('|'):
		c2 = 1;
		break;
	default:
		break;
	}

	return c1 > c2;
}

int main()
{
	int kase = 1;
	char cmd[MAX_LEN];
	while (cin.getline(cmd, MAX_LEN))
	{
		//入栈
		for (int i = 0; i < strlen(cmd); i++)
		{
			if (cmd[i] == ' ')
				continue;
			//运算
			else if (cmd[i] == 'V' || cmd[i] == 'F')
			{
				values.push(cmd[i]);
			}
			else{
					while (!operators.empty()&&cmp_priority(operators.top(),cmd[i] ))//要入站的优先级低
						Operate_by_operator(operators.pop(),&values,&operators);
					operators.push(cmd[i]);
				}	
		}
		while (!operators.empty())
		{
			Operate_by_operator(operators.pop(),&values, &operators);
		}
		printf("Expression %d: %c\n", kase++, values.pop());
	}
	return 0;
}

//(V)没处理好，没弄清楚)入栈操作