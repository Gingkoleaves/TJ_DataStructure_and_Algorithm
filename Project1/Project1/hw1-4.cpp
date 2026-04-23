#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

#define Diamond_Index 0
#define Spade_Index 1
#define Heart_Index 2
#define Club_Index 3

const char Cards_Style[][8] = { "Diamond","Spade","Heart","Club" };
const char Cards_Value[][13]{ "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

struct Card {
	char style;//花色的序号
	char value;//牌面的序号
	Card* prev=NULL;
	Card* next=NULL;

	
};

struct Cards_pile {
	Card* top;
	Card* bottom;
	bool is_reverse = false;//反转排序与否

	Cards_pile()
	{
		//设置头结点
		Card* head = new Card;
		head->style = -1;
		head->value = -1;

		//设置头尾指针
		top = head;
		bottom = head;
	}

	void Append_2_Bottom(char* style, char* value)
	{
		int style_num = -1;
		for (int i = 0; i < 4; i++)
			if (!strcmp(style, Cards_Style[i]))
				style_num = i;

		int value_num = -1;
		for (int i = 0; i < 13; i++)
			if (!strcmp(value, Cards_Value[i]))
				value_num = i;

		if (value_num==-1 || style_num==-1)//NULL与0重合
			return;

		//初始化卡牌
		Card* New_Card = new Card;
		New_Card->style = style_num;
		New_Card->value = value_num;

		if (is_reverse)
		{
			New_Card->prev = top;

			//加入牌堆
			New_Card->next = top->next;
			top->next = New_Card;
			if (!(New_Card->next))//null时移动bottom
				bottom = New_Card;
			else
				New_Card->next->prev = New_Card;
		}
		else
		{
			New_Card->next = NULL;

			//加入牌堆
			bottom->next = New_Card;
			New_Card->prev = bottom;
			bottom = New_Card;
		}
	}

	void Pop()
	{
		if (bottom == top)
			printf("NULL\n");
		else
		{
			if (is_reverse)
			{
				printf("%s %s\n", Cards_Style[bottom->style], Cards_Value[bottom->value]);
				Card* mid=bottom;
				bottom = bottom->prev;
				bottom->next = NULL;
				delete mid;
			}
			else {
				printf("%s %s\n", Cards_Style[top->next->style], Cards_Value[top->next->value]);
				Card* mid = top->next;
				top->next = mid->next;
				if (mid->next)
					mid->next->prev = top;
				else
				{
					bottom = top;
					bottom->next = NULL;
				}
				delete mid;
			}
		}
	}

	void Revert_Card_Pile()
	{
		is_reverse = !is_reverse;
	}

	void Extract_Style(char* style)
	{
		int style_num=-1;
		for (int i = 0; i < 4; i++)
			if (!strcmp(style, Cards_Style[i]))
				style_num = i;	//重定义

		if (style_num==-1)
			return;

		Cards_pile Extr;
		Card* traverse = top->next;
		while (traverse)
		{
			Card* mid = traverse->next;
			if (traverse->style == style_num)
			{
				//断开
				traverse->prev->next = traverse->next;
				if (traverse->next)
					traverse->next->prev = traverse->prev;
				else
				{
					bottom = traverse->prev;
					bottom->next = NULL;
				}

				//有序连接
				Card* pos = Extr.top;
				while (pos->next)
				{					
					if (is_reverse ? (pos->next->value) > traverse->value :(pos->next->value) < traverse->value)
						pos = pos->next;//没有更新
					else
						break;		
				}

				//pos为traverse前驱结点
				traverse->next = pos->next;
				pos->next = traverse;
				traverse->prev = pos;

				if (traverse->next)
					traverse->next->prev = traverse;
				else
				{
					Extr.bottom = traverse;
					Extr.bottom->next = NULL;
				}
			}

			traverse = mid;//traverse指向的结点连接到新表上，不能再通过traverse访问原表下一个card
		}


		//连接到牌堆顶部，注意reverse
		//注意非空Extr，注意空的this
		if (Extr.top->next)
		{
			if (is_reverse)
			{
				bottom->next = Extr.top->next;
				Extr.top->next->prev = bottom;

				bottom = Extr.bottom;
				delete Extr.top;
			}
			else {
				if (top->next)
				{
					top->next->prev = Extr.bottom;
					Extr.bottom->next = top->next;

					Card* del = top;
					top = Extr.top;
					delete del;
				}
				else
				{
					delete top;
					bottom = Extr.bottom;
					top = Extr.top;
				}
			}
		}
	}

	void Print_pile()
	{
		Card* Traverse;
		if (is_reverse)
		{
			Traverse = bottom;
			while (Traverse->prev)
			{
				printf("%s %s\n", Cards_Style[Traverse->style], Cards_Value[Traverse->value]);
				Traverse = Traverse->prev;
			}
		}
		else
		{
			Traverse = top->next;
			while (Traverse)
			{
				printf("%s %s\n", Cards_Style[Traverse->style], Cards_Value[Traverse->value]);
				Traverse = Traverse->next;
			}
		}
	}
};


Cards_pile Cdp;
char str1[30];
char opt[10];
char card_style[10];
char card_value[4];

int main()
{
	int n;
	scanf("%d", &n);
	cin.ignore();

	while (n--)
	{
		cin.getline(str1, 30);
		switch (str1[0])
		{
		case('A'):
			sscanf(str1, "%s %s %s", opt, card_style, card_value);
			Cdp.Append_2_Bottom(card_style, card_value);
			break;
		case('E'):
			sscanf(str1, "%s %s", opt, card_style);
			Cdp.Extract_Style(card_style);
			break;
		case('R'):
			Cdp.Revert_Card_Pile();
			break;
		case('P'):
			Cdp.Pop();
			break;
		default:
			break;
		}
	}
	Cdp.Print_pile();
	return 0;
}


