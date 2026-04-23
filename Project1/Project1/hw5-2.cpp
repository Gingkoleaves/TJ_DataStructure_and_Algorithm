//#include <iostream>
//#include <cstring>
//#define Seq_Maxlen 1005
//using namespace std;
//
//struct Node{
//	int value;
//	int repetition;
//	Node* lnode=nullptr;
//	Node* rnode=nullptr;
//};
//
//void Delete_Tree(Node*& nod1)
//{
//	if (nod1->lnode)Delete_Tree(nod1->lnode);
//	if (nod1->rnode)Delete_Tree(nod1->rnode);
//	delete nod1;
//}
//
//class BST {
//private:
//public:
//	Node* Root;
//	BST(){
//		Root = new Node;
//		Root->repetition = 0;//表示空表
//	}
//	~BST(){
//		Delete_Tree(Root);
//	}
//	void Insert(const int& ins)
//	{
//		Node* Cur_Node = Root;
//
//		if (Root->repetition == 0)
//		{
//			Root->value = ins;
//			Root->repetition = 1;
//			return;
//		}
//		while (1)
//		{
//			if (ins < Cur_Node->value)
//			{
//				if(Cur_Node->lnode!=nullptr)
//					Cur_Node = Cur_Node->lnode;
//				else
//				{
//					Cur_Node->lnode = new Node;
//					Cur_Node->lnode->value = ins;
//					Cur_Node->lnode->repetition = 1;
//					break;
//				}
//			}
//			else if (ins > Cur_Node->value)
//			{
//				if(Cur_Node->rnode!=nullptr)
//					Cur_Node = Cur_Node->rnode;
//				else
//				{
//					Cur_Node->rnode = new Node;
//					Cur_Node->rnode->value = ins;
//					Cur_Node->rnode->repetition = 1;
//					break;
//				}
//			}
//			else
//			{
//				Cur_Node->repetition += 1;
//				break;
//			}
//		}
//	}
//	int Search(const int& ins,Node* & u_search,Node* &u_want_parent)
//	{
//		Node* Cur_Node = Root;
//		while (1)
//		{
//			if (ins < Cur_Node->value)
//			{
//				if (Cur_Node->lnode != nullptr)
//				{
//					u_want_parent = Cur_Node;
//					Cur_Node = Cur_Node->lnode;
//				}
//				else				
//					return 0;
//			}
//			else if (ins > Cur_Node->value)
//			{
//				if (Cur_Node->rnode != nullptr)
//				{
//					u_want_parent = Cur_Node;
//					Cur_Node = Cur_Node->rnode;
//				}
//				else
//					return 0;
//			}
//			else
//			{
//				u_search = Cur_Node;
//				return 1;
//			}
//		}
//	}
//	int Search_repetition(const int& search)
//	{
//		Node* u_want;
//		Node* u_want_parent;
//		if (!Search(search, u_want, u_want_parent))return 0;//没有找到
//		return u_want->repetition;
//	}
//	Node* find_forw(const int& search)
//	{
//		Node* Cur_Node = Root;
//		Node* forw_Node = nullptr;
//
//		while (Cur_Node != nullptr)
//		{
//			if (Cur_Node->value < search)
//			{
//				forw_Node = Cur_Node;
//				Cur_Node = Cur_Node->rnode;
//			}
//			else if (Cur_Node->value > search)
//			{
//				Cur_Node = Cur_Node->lnode;
//			}
//			else
//			{
//				forw_Node = Cur_Node->lnode== nullptr ? forw_Node : Find_max(Cur_Node->lnode);
//				return forw_Node;
//			}
//		}
//
//		return forw_Node;
//
//	}
//	Node* Find_max(Node* root)
//	{
//		if (root == nullptr)
//			return nullptr;
//
//		Node* Cur_Node = root;
//		while (Cur_Node->rnode != nullptr)
//			Cur_Node = Cur_Node->rnode;
//
//		return Cur_Node;
//	}
//	Node* Find_min(Node* root,Node*& parent)
//	{
//		if (root == nullptr)
//			return nullptr;
//
//		Node* Cur_Node = root;
//		parent = root;
//		while (Cur_Node->lnode != nullptr)
//		{
//			parent = Cur_Node;
//			Cur_Node = Cur_Node->lnode;
//		}
//
//		return Cur_Node;
//	}
//	int Delete(const int& dele)
//	{
//		Node* u_want;
//		Node* u_want_parent;
//		Node* parent;
//		if (!Search(dele, u_want, u_want_parent))return 0;//没有找到
//
//		if (u_want->repetition > 1)u_want->repetition -= 1;
//		else
//		{
//			if (u_want->lnode == nullptr && u_want->rnode == nullptr)
//			{
//				if (u_want_parent->lnode == u_want)u_want_parent->lnode = nullptr;
//				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = nullptr;
//				delete u_want;
//			}
//			else if (u_want->lnode == nullptr)
//			{
//				if (u_want_parent->lnode == u_want)u_want_parent->lnode = u_want->rnode;
//				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = u_want->rnode;
//				delete u_want;
//			}
//			else if (u_want->rnode == nullptr)
//			{
//				if (u_want_parent->lnode == u_want)u_want_parent->lnode = u_want->lnode;
//				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = u_want->lnode;
//				delete u_want;
//			}
//			else
//			{
//				Node* right_min = Find_min(u_want->rnode, parent);
//				if(right_min !=parent)parent->lnode = nullptr;
//				right_min->lnode = u_want->lnode;
//
//				if (u_want->rnode != right_min)right_min->rnode = u_want->rnode;
//				else right_min->rnode = nullptr;
//
//				if (u_want_parent->lnode == u_want)u_want_parent->lnode = right_min;
//				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = right_min;
//				delete u_want;
//			}
//		}
//		return 1;//成功删除
//	}
//};
//
//
//int main()
//{
//	BST bst;
//	Node* parent = bst.Root;
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; i++)
//	{
//		int op,arg;
//		cin >> op;
//		switch (op)
//		{
//		case(1):
//			cin >> arg;
//			bst.Insert(arg);
//			break;
//		case(2):
//			cin >> arg;
//			if(!bst.Delete(arg))
//				cout<<"None"<<endl;
//			break;
//		case(3):
//			cin >> arg;
//			cout<<bst.Search_repetition(arg)<<endl;
//			break;
//		case(4):
//			cout<<bst.Find_min(bst.Root, parent)->value<<endl;
//			break;
//		case(5):
//			cin >> arg;
//			Node* res=bst.find_forw(arg);
//			if (res == nullptr)
//				cout << "None" << endl;
//			else cout << res->value << endl;
//			break;
//		}
//	}
//	return 0;
//}


#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define Seq_Maxlen 1000
using namespace std;

struct Node {
	int value;
	int repetition;
	Node* lnode = nullptr;
	Node* rnode = nullptr;
};

void Delete_Tree(Node*& nod1)
{
	if (nod1->lnode)Delete_Tree(nod1->lnode);
	if (nod1->rnode)Delete_Tree(nod1->rnode);
	delete nod1;
}

class BST {
private:
public:
	Node* Root;
	BST() {
		Root = new Node;
		Root->repetition = 0;//表示空表
	}
	~BST() {
		Delete_Tree(Root);
	}
	void Insert(const int& ins)
	{
		Node* Cur_Node = Root;

		if (Root->repetition == 0)
		{
			Root->value = ins;
			Root->repetition = 1;
			return;
		}

		while (1)
		{
			if (ins < Cur_Node->value)
			{
				if (Cur_Node->lnode != nullptr)
					Cur_Node = Cur_Node->lnode;
				else
				{
					Cur_Node->lnode = new Node;
					Cur_Node->lnode->value = ins;
					Cur_Node->lnode->repetition = 1;
					break;
				}
			}
			else if (ins > Cur_Node->value)
			{
				if (Cur_Node->rnode != nullptr)
					Cur_Node = Cur_Node->rnode;
				else
				{
					Cur_Node->rnode = new Node;
					Cur_Node->rnode->value = ins;
					Cur_Node->rnode->repetition = 1;
					break;
				}
			}
			else
			{
				Cur_Node->repetition += 1;
				break;
			}
		}
	}
	int Search(const int& ins, Node*& u_search, Node*& u_want_parent)
	{
		Node* Cur_Node = Root;
		u_want_parent = nullptr;
		while (1)
		{
			if (ins < Cur_Node->value)
			{
				if (Cur_Node->lnode != nullptr)
				{
					u_want_parent = Cur_Node;
					Cur_Node = Cur_Node->lnode;
				}
				else
					return 0;
			}
			else if (ins > Cur_Node->value)
			{
				if (Cur_Node->rnode != nullptr)
				{
					u_want_parent = Cur_Node;
					Cur_Node = Cur_Node->rnode;
				}
				else
					return 0;
			}
			else
			{
				u_search = Cur_Node;
				return 1;
			}
		}
	}
	int Search_repetition(const int& search)
	{
		Node* u_want;
		Node* u_want_parent;
		if (!Search(search, u_want, u_want_parent))return 0;//没有找到
		return u_want->repetition;
	}
	Node* find_forw(const int& search)
	{
		Node* Cur_Node = Root;
		Node* forw_Node = nullptr;

		while (1)
		{
			if (Cur_Node == nullptr)
				return forw_Node;

			if (Cur_Node->value < search)
			{
				forw_Node = Cur_Node;
				Cur_Node = Cur_Node->rnode;
			}
			else if (Cur_Node->value > search)
			{
				Cur_Node = Cur_Node->lnode;
			}
			else
			{
				forw_Node = Cur_Node->lnode == nullptr ? forw_Node : Find_max(Cur_Node->lnode);
				return forw_Node;
			}
		}
	}
	Node* Find_max(Node* root)
	{
		Node* Cur_Node = root;
		while (Cur_Node->rnode != nullptr)
			Cur_Node = Cur_Node->rnode;

		return Cur_Node;
	}
	Node* Find_min(Node* root,Node*&parent)
	{
		Node* Cur_Node = root;
		parent = nullptr;
		while (Cur_Node->lnode != nullptr)
		{
			parent = Cur_Node;
			Cur_Node = Cur_Node->lnode;
		}

		return Cur_Node;
	}
	int Delete(const int& dele)
	{
		Node* u_want;
		Node* u_want_parent;
		Node* parent=nullptr;
		if (!Search(dele, u_want, u_want_parent))return 0;//没有找到
		
		if (u_want->repetition > 1)u_want->repetition -= 1;
		else
		{
			if (u_want->lnode == nullptr && u_want->rnode == nullptr)
			{
				if (u_want_parent == nullptr)
					Root->repetition = 0;	
				else if (u_want_parent->lnode == u_want)u_want_parent->lnode = nullptr;
				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = nullptr;
				
				if(u_want!=Root)delete u_want;
			}
			else if (u_want->rnode == nullptr)
			{
				if (u_want_parent == nullptr)
				{
					Node* mid = Root->lnode;
					delete Root;
					Root = mid;
					return 1;
				}

				else if (u_want_parent->lnode == u_want)u_want_parent->lnode = u_want->lnode;
				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = u_want->lnode;

				if (u_want != Root)delete u_want;
			}			
			else
			{
				Node* right_min = Find_min(u_want->rnode,parent);
				if (parent)
					parent->lnode = right_min->rnode;				

				right_min->lnode = u_want->lnode;
				if (right_min != u_want->rnode)right_min->rnode = u_want->rnode;				

				if (u_want_parent == nullptr)
				{
					delete Root;
					Root = right_min;
					return 1;
				}
				else if (u_want_parent->lnode == u_want)u_want_parent->lnode = right_min;
				else if (u_want_parent->rnode == u_want)u_want_parent->rnode = right_min;

				delete u_want;
			}
		}
		return 1;//成功删除
	}
};


int main()
{
	BST bst;
	Node* buf,*res=nullptr,*ptr=nullptr;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int op, arg;
		cin >> op;
		switch (op)
		{
		case(1):
			cin >> arg;
			bst.Insert(arg);
			break;
		case(2):
			cin >> arg;
			if (!bst.Delete(arg))
				cout << "None" << endl;
			break;
		case(3):
			cin >> arg;
			cout << bst.Search_repetition(arg) << endl;
			break;
		case(4):
			ptr = bst.Find_min(bst.Root, buf);
			cout <<(ptr?ptr->value:0) << endl;
			break;
		case(5):
			cin >> arg;
			res = bst.find_forw(arg);
			if (res == nullptr)
				cout << "None" << endl;
			else cout << res->value << endl;
			break;
		}
	}
	return 0;
}