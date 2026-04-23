#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<iomanip>

using namespace std;

//应当用顺序表
struct Node {
	int data;
	Node* next;
	Node* prev;
};

struct Big_Integer {
	static const int BASE = 100000000;
	static const int WIDTH = 8;

	Node* begin;
	Node* end;
	int length = 0;

	Big_Integer()
	{
		begin = new Node;
		end = begin;

		//头节点设置
		begin->next = NULL;
		begin->prev = NULL;
		begin->data = 0;
	}	
	
	Big_Integer(long long int num)
	{
		begin = new Node;
		end = begin;

		//头节点设置
		begin->next = NULL;
		begin->prev = NULL;
		begin->data = 0;

		{ *this = num; }
	}

	template<size_t N>
	Big_Integer(char (&s)[N])
	{
		begin = new Node;
		end = begin;

		//头节点设置
		begin->next = NULL;
		begin->prev = NULL;
		begin->data = 0;

		*this = s; // 使用已有的赋值操作符
	}

	void Big_Integer_Clear()
	{
		Node* start = this->begin;
		while (start->next)
			start=start->next;
		
		while (start->prev)
		{
			Node* mid = start->prev;
			delete start;
			start = mid;
		}

		end = begin;
		length = 0;
	}

	Big_Integer operator = (long long num)
	{
		Big_Integer_Clear();
		Node* pp = begin;
		do
		{
			Node* p = new Node;
			p->next = NULL;

			pp->next = p;
			p->prev = pp;

			p->data = num % BASE;
			num /= BASE;

			end = p;
			pp = p;
			length++;
		} while (num > 0);

		return *this;
	}

	template<size_t N>
	Big_Integer operator = (char (&str)[N])
	{
		Big_Integer_Clear();
		Node* pp = begin;
		int len = (strlen(str) - 1) / WIDTH + 1;	//	len段
		for (int i = 0; i < len; i++)
		{
			int end = strlen(str) - i * WIDTH;
			int beg = max(0, end - WIDTH);
			char mid[WIDTH + 2] = { 0 };
			int mid_num = 0;

			strncpy(mid, &str[beg], WIDTH);
			sscanf(mid, "%d", &mid_num);

			Node* p = new Node;
			p->next = NULL;

			pp->next = p;
			p->prev = pp;

			p->data = mid_num;

			this->end = p;
			pp = p;
			length++;
		}
		return *this;
	}

	Big_Integer operator + (Big_Integer &b2)
	{
		Big_Integer C;//result

		Node* np1 = begin;
		Node* np2 = b2.begin;

		for (int i = 1, g = 0;; i++)
		{
			if (g == 0 && i > length && i > b2.length)break;//g为进位,i为下标，所以>=
			int x = g;//x、g配合进位

			if (i <= length)
			{
				np1 = np1->next; 
				x += np1->data; 
			}
			if (i <= b2.length) 
			{
				np2 = np2->next; 
				x += np2->data; 
			}

			//申请新节点
			Node* p1 = new Node;
			C.end->next = p1;
			p1->next = NULL;
			p1->prev = C.end;
			C.end = p1;

			p1->data = x % BASE;
			g = x / BASE;
			C.length++;
		}
		return C;
	}

	Big_Integer operator + (long long int i1)
	{
		Big_Integer b1(i1);
		return ((*this) + b1);
	}

	void _set_0()
	{
		Node* start = begin->next;
		if (!start)return;
		while (start)
		{
			start->data = 0;
			start=start->next;
		}
	}

	Big_Integer operator * (Big_Integer b)
	{
		static const int HALF_BASE = 10000;
		Big_Integer c=0;

		Big_Integer Mid;
		if (b.length == 1 && b.begin->next->data == 0)
		{
			c = 0;
			return c;
		}
	

		//预先申请结点
		int maxn = max(b.length, length);
		Node* cur = Mid.begin;
		for (int i = 0; i < maxn+1; i++)
		{
			Node* NeW_NoDe = new Node;

			NeW_NoDe->next = NULL;
			NeW_NoDe->prev = cur;
			NeW_NoDe->data = 0;

			cur->next = NeW_NoDe;
			cur = cur->next;
			Mid.end = cur;
			Mid.length++;
		}

		Node* start_mid = Mid.begin->next;
		Node* start_this = begin->next;
		for (int i = 1,g=0;; i++)
		{
			Mid._set_0();

			if (i> length)break;
			Node* traverse_b = b.begin->next;
			Node* traverse_mid = start_mid;

			for (int j = 1;; j++)
			{
				if (g == 0 && j > b.length)break;


				int bb = 0;
				if(j<=b.length)
					bb += ((start_this->data)%HALF_BASE)* ((traverse_b->data) % HALF_BASE);

				int b1 = 0; 
				if (j <= b.length)
					b1 = ((start_this->data) / HALF_BASE)*((traverse_b->data) % HALF_BASE);

				int b2 = 0;
				if (j <= b.length)
					b2 = ((traverse_b->data) / HALF_BASE)* ((start_this->data) % HALF_BASE);

				int t = 0;
				if (j <= b.length)
					t = ((traverse_b->data) / HALF_BASE)*((start_this->data) / HALF_BASE);


				int ansl = ((long long)g + (long long)bb + (long long)b2* HALF_BASE + (long long)b1 * HALF_BASE) % BASE;
				int ansh = ((long long)g + (long long)bb + (long long)b2 *HALF_BASE +(long long)b1 * HALF_BASE) / BASE + t;


				traverse_mid->data += ansl;//大bug，应当相加而非赋值
				g = ansh;

				//这里有问题：

				
				if(traverse_b->next)
					traverse_b = traverse_b->next;
				traverse_mid = traverse_mid->next;			
			}


			

			//mid尾部加i-1格0
			for (int t = 0; t < i - 1; t++)
			{
				Node* Zero = new Node;
				Zero->data = 0;
				Zero->next = Mid.begin->next;
				Zero->prev = Mid.begin;
				Mid.begin->next = Zero;
				if (Zero->next)
					Zero->next->prev = Zero;
				Mid.length++;
			}
			//赋值
			c =c+ Mid;

			//mid去尾部0
			for (int t = 0; t < i - 1; t++)
			{
				Node* del = Mid.begin->next;
				Mid.begin->next = del->next;
				del->next->prev = Mid.begin;
				delete del;
				Mid.length--;
			}

			
			//start_this后移一个格
			if(start_this->next)
				start_this = start_this->next;

		}

		//清除首0
		Node* c_end = c.end;
		while((c_end->data == 0)&&c_end->prev)
		{
			Node* mid = c_end->prev;
			delete c_end;
			c_end = mid;
			c.length--;
		}
		c.end = c_end;
		c.end->next = NULL;
		return c;
	}
	
	void Big_Integer_Print()
	{
		Node* cur = end;
		while(cur->prev)
		{
			if (cur == end)
				printf("%.1d", cur->data);
			else
				printf("%.8d", cur->data);

			cur = cur->prev;
		}
	}
};



/*

struct Big_Integer
{
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> v;

	// 注意，在Big_Integer x1=13434531523982734中，即在初始化中，不涉及赋值运算符
	// 而是尝试调用构造函数Big_Integer(long long value)或其他形参的构造函数，这些形参与ll有隐式类型转换
	Big_Integer(long long int num = 0) { *this = num; }
	Big_Integer(const string& s)
	{
		*this = s; // 使用已有的赋值操作符
	}
	Big_Integer operator = (long long num)
	{
		v.clear();
		do {
			v.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	Big_Integer operator = (string& s)
	{
		v.clear();
		int mid, len = (s.length() - 1) / WIDTH + 1;	//	len段
		for (int i = 0; i < len; i++)
		{
			int end = s.length() - i * WIDTH;
			int beg = max(0, end - WIDTH);
			sscanf(s.substr(beg, end - beg).c_str(), "%d", &mid);
			v.push_back(mid);
		}
		return *this;
	}
	Big_Integer operator = (Big_Integer b1)
	{
		v.clear();
		v = b1.v;
		return *this;
	}
	Big_Integer operator + (Big_Integer b)
	{
		Big_Integer c;//result
		c.v.clear();
		for (int i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= v.size() && i >= b.v.size())break;//g为进位,i为下标，所以>=
			int x = g;//x、g配合进位
			if (i < v.size()) x += v[i];
			if (i < b.v.size())	x += b.v[i];
			c.v.push_back(x);
			g = x / BASE;
		}
		return c;
	}
	Big_Integer operator += (Big_Integer &b)
	{
		*this = *this + b; return *this;
	}
	Big_Integer operator * (Big_Integer &b)
	{
		static int HALF_BASE = 10000;

		Big_Integer c;
		c.v.clear();

		Big_Integer A;
		A.v.assign(v.begin() + v.size() / 2, v.end() - 1);
		Big_Integer B;
		B.v.assign(v.begin() ,v.begin()+ v.size() / 2-1);
		Big_Integer C;
		C.v.assign(b.v.begin() + b.v.size() / 2, b.v.end() - 1);
		Big_Integer D;
		D.v.assign(b.v.begin(), b.v.begin() + b.v.size() / 2 - 1);

		A*B 


		return c;
	}
	bool operator < (const Big_Integer b)
	{
		if (v.size() != b.v.size()) return v.size() < b.v.size();
		for (int i = v.size() - 1; i >= 0; i--)
			if (v[i] != b.v[i]) return v[i] < b.v[i];
		return false;//相等
	}

};

// 一般在类外定义输入输出流运算符。因为如果在类内，左操作变量默认为*this，与需要的输出流对象作为左操作数不符
// cout是标准输出流对象
ostream& operator << (ostream& out, Big_Integer& x)
{
	out << x.v.back();
	for (int i = x.v.size() - 2; i >= 0; i--)
	{
		char buf[20];
		sprintf(buf, "%08d", x.v[i]);
		for (int j = 0; j < strlen(buf); j++)out << buf[j];
	}
	return out;
}

istream& operator >> (istream& in, Big_Integer& x)
{
	string s;
	if (!(in >> s)) return in;
	x = s;
	return in;
}

*/

int main()
{
	long long int N, A;
	cin>>N>>A;

	Big_Integer b1 =A;
	Big_Integer b2 = N;
	Big_Integer sum = 0;

	
	for (long long int i = N; i>=1; i--)
	{
		sum=(sum + i);
		sum = sum * b1;
	}
	sum.Big_Integer_Print();
	

	return 0;
}