#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//tyepdef [真正类型] 假名1,假名2,*假名3（是指向真正类型的指针）,&假名4(是真正类型的引用)

struct Node {
	float coef;
	short expn;
	Node* prev;
	Node* next;
};

//有序排列的一元多项式链表，不循环
struct Polynomial{
	Node* begin;//头指针
	Node* end;//尾指针
	int length ;//除去头结点的长度

	//构造函数
	Polynomial() {
		begin = (Node*)new Node;//头节点

		//头结点设置
		begin->coef = 0;
		begin->expn = 0;
		begin->prev=NULL;
		begin->next = NULL;

		//多项式设置
		end = begin;
		length = 0;
	}

	// 若存在，则返回true和指向该项的指针；不存在，则返回false和指向首个
	// 大于iexpn的项的前驱的指针（如果不存在大于iexpn的项，返回指向末项的指针）
	bool Polynomial_Search(short iexpn,Node* (&q))
	{
		Node* pp=begin,*p = begin->next;
		while (p && (p->expn < iexpn))
		{
			pp = p; 
			p = p->next;
		}
		if (!p || p->expn > iexpn)
		{
			q = pp;
			return false;
		}
		else
		{
			q = p;
			return true;
		}
	}

	//按序插入一项，若没有，则在对应位置新建节点
	void Polynomial_Insert_Ordered(float icoef, short iexpn)
	{
		Node* p=begin;
		bool is_exist=Polynomial_Search(iexpn,p);
		//当存在对应iexpn结点
		if(is_exist)
		{
			p->coef += icoef;
			//如果coef==0，realloc
			if (p->coef == 0)
			{
				p->prev->next = p->next;
				if(p->next)
					p->next->prev = p->prev;
				else//p是最后一个结点
					end = p->prev;
				delete p;
				length -= 1;
			}
		}
		else//不存在
		{
			Node* mid = (Node*)new Node;
			mid->coef = icoef;
			mid->expn = iexpn;

			mid->next = p->next;
			if (p->next)//p->next!=NULL时,下一个结点的prev变化
				p->next->prev = mid;
			else//p->next==NULL时，要更新尾指针
				end = mid;

			p->next = mid;
			mid->prev = p;

			length += 1;
		}
	}

	//两个多项式相加
	Polynomial Polynomial_Add(const Polynomial& p2)
	{
		Polynomial res;

		Node* ptr2 = p2.begin->next;
		//用p2逐项加p1
		while (ptr2)
		{
			res.Polynomial_Insert_Ordered(ptr2->coef, ptr2->expn);
			ptr2 = ptr2->next;
		}

		Node* ptr1 = this->begin->next;
		while (ptr1)
		{
			res.Polynomial_Insert_Ordered(ptr1->coef, ptr1->expn);
			ptr1 = ptr1->next;
		}
		return res;
	}

	//两个多项式相乘
	Polynomial Polynomial_Multi(const Polynomial& p2)
	{
		Polynomial res;

		Node* ptr2 = p2.begin->next;
		//用p2逐项乘p1
		while (ptr2)
		{
			Node* ptr1 = this->begin->next;
			while (ptr1)
			{
				float coef_r = ptr1->coef * ptr2->coef;
				short expn_r = ptr1->expn + ptr2->expn;
				res.Polynomial_Insert_Ordered(coef_r, expn_r);

				ptr1 = ptr1->next;
			}
			ptr2 = ptr2->next;
		}
		return res;
	}

	void Polynomial_Print()
	{
		Node* cur = begin->next;
		while (cur)
		{
			cout << cur->coef << ' ' << cur->expn << ' ';
			cur=cur->next;
		}
		cout << endl;
	}

};




int main()
{
	Polynomial p1;
	short m;
	scanf("%hd", &m);

	for (short i = 0; i <m; i++)
	{
		short expn;
		float coef;
		scanf("%f%hd", &coef, &expn);
		p1.Polynomial_Insert_Ordered(coef, expn);
	}


	Polynomial p2;
	short n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		short expn;
		float coef;
		scanf("%f%hd", &coef, &expn);
		p2.Polynomial_Insert_Ordered(coef, expn);
	}


	short opt;
	scanf("%hd", &opt);
	switch (opt)
	{
	case(0):
		p1.Polynomial_Add(p2).Polynomial_Print();
		break;
	case(1):
		p1.Polynomial_Multi(p2).Polynomial_Print();
		break;
	case(2):
		p1.Polynomial_Add(p2).Polynomial_Print();
		p1.Polynomial_Multi(p2).Polynomial_Print();
		break;
	}
	/*

	//int i()理解成函数的声明，所以没有参数的构造函数不能 struct name()调用
	Polynomial p1;
	p1.Polynomial_Insert_Ordered(3, 5);
	p1.Polynomial_Print();

	Polynomial p2;
	p2.Polynomial_Insert_Ordered(2, 7);
	p2.Polynomial_Insert_Ordered(3, 4);
	p2.Polynomial_Print();

	Polynomial p3;
	p3 = p1.Polynomial_Add(p2);
	p3.Polynomial_Print();

	p3 = p1.Polynomial_Multi(p2);
	p3.Polynomial_Print();

	*/


	return 0;
}