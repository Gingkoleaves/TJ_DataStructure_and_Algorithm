#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define MAX_LEN 100
#define INITIAL_LEN 0
#define SENTENCE 32
#define INCERMENT 10


struct Stu_List
{
	struct stu
	{
		char Index[SENTENCE];
		char Name[SENTENCE];
	};

	int max_len;
	int cur_len;
	stu* head;

	Stu_List()
	{
		//动态申请内存
		head = new stu[MAX_LEN];
		if (!head)
			exit(-1);
		max_len = MAX_LEN;
		cur_len = INITIAL_LEN;
		return;
	}

	~Stu_List()
	{
		if(head)//补充
			delete[] head;
		cur_len = 0;//补
		max_len = 0;
	}

	void Stu_List_Update()
	{
		//申请新内存
		max_len += INCERMENT;
		stu* mid = new stu[max_len];
		if (!mid)
			exit(-1);

		//复制原内容
		memcpy(mid, head, cur_len * sizeof(stu));
		//释放数组内存
		if(head)
			delete[] head;
		//更新属性
		head = mid;
	}

	template <size_t N>
	void Stu_List_Append(char(&Index)[N], char(&Name)[N])
	{
		//溢出
		if (cur_len >= max_len)
			Stu_List_Update();

		memset((head + cur_len)->Index, 0, SENTENCE*sizeof(char));		//清理输入区域
		memset((head + cur_len)->Name, 0, SENTENCE * sizeof(char));

		memcpy((head + cur_len)->Index, Index, strlen(Index)+1);//数组大小而不是指针大小sizeof(InDEX)
		memcpy((head + cur_len)->Name, Name, strlen(Name)+1);
		cur_len++;

		return;
	}

	//从指定pos后移一位
	int _move_backward(int pos)
	{
		if (pos<1 || pos>cur_len)
			return -1;

		for (int i = cur_len; i >= pos; i--)
			memcpy(head + i, head + i - 1, sizeof(stu));

		return 0;
	}

	//将指定pos用前移覆盖掉
	int _move_forward(int pos)
	{
		if (pos<1 || pos>cur_len)
			return -1;

		for (int i = pos; i < cur_len; i++)
			memcpy(head + i - 1, head + i, sizeof(stu));

		return 0;
	}

	//bug：当长度为0不能insert,insert合法位置是什么（能不能在0插入，能不能在cur_len后一位插入），没有描述清楚
	template <size_t N>
	int Stu_List_Insert(int insert_pos, char(&iIndex)[N], char(&iName)[N])
	{
		if (insert_pos<1 || insert_pos>cur_len+1)
			return -1;
		

		//留出空位
		if (cur_len >= max_len)//bug：>=
			Stu_List_Update();

		_move_backward(insert_pos);

		memset((head + insert_pos - 1)->Index, 0, SENTENCE);//用\0填充sentence长度
		memset((head + insert_pos - 1)->Name, 0, SENTENCE);

		memcpy((head + insert_pos - 1)->Index, iIndex, strlen(iIndex)+1);
		memcpy((head + insert_pos - 1)->Name, iName, strlen(iName)+1);
		cur_len++;

		return 0;
	}

	int Stu_List_Remove(int pos)
	{
		if (pos<1 || pos>cur_len)
			return -1;		

		_move_forward(pos);
		cur_len--;

		return 0;
	}

	template <size_t N>
	void  Stu_List_Check_Name(char(&Name)[N])
	{
		for (int i = 0; i < cur_len; i++)
		{
			if (strcmp((head + i)->Name, Name) == 0)
			{
				//输出位置学号姓名
				printf("%d %s %s\n", i + 1, (head + i)->Index, (head + i)->Name);
				return;
			}
		}
		printf("%d\n", -1);
		return;
	}
	
	template <size_t N>
	void Stu_List_Check_Index(char(&Index)[N])
	{
		for (int i = 0; i < cur_len; i++)
		{
			if (strcmp((head + i)->Index, Index) == 0)
			{
				//输出位置学号姓名
				printf("%d %s %s\n", i + 1, (head + i)->Index, (head + i)->Name);
				return;
			}
		}
		printf("%d\n", -1);
		return;
	}
};
/*
* ///
* ///
* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
* strcmp和strncmp，前者需要两个字符串完全相同（长度相同、字符相同），后者只需要前n个字符相同
* ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
* ///
* ///
*/

int main()
{
	
	Stu_List SL;

	char cmd[SENTENCE * 3] = { 0 };
	char cmd1[SENTENCE];
	char cmd2[SENTENCE];
	char Index[SENTENCE];
	char Name[SENTENCE];
	int pos;

	int n;
	cin>>n;
	while(n--)
	{
		cin>>Index>>Name;
		SL.Stu_List_Append(Index, Name);
	}

	while (cin.getline(cmd, 3*SENTENCE))
	{
		if (cmd[0] == 'e')
		{
			printf("%d\n", SL.cur_len);
			break;
		}

		switch (cmd[0])
		{
		case('i'):
			sscanf(cmd, "%s %d %s %s", cmd1, &pos, Index, Name);
			cout<<SL.Stu_List_Insert(pos, Index, Name)<<endl;
			break;
		case('r'):
			sscanf(cmd, "%s%d", cmd1, &pos);
			cout<<SL.Stu_List_Remove(pos)<<endl;
			break;
		case('c'):
			sscanf(cmd, "%s %s %s", cmd1, cmd2, Name);
			if (cmd2[1] == 'o')
				SL.Stu_List_Check_Index(Name);
			else if (cmd2[1] == 'a')
				SL.Stu_List_Check_Name(Name);
			else
				break;
		default:
			break;
		}
	}
	
	return 0;
}

