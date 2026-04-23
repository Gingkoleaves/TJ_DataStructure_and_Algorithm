#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

long long get_hash(const string& s1)
{
	long long code=0;
	for (int i = 0; i < s1.size(); i++)
	{
		code += (i + 1) *(s1[i]%10);
	}
	return code;
}

struct Node {
	Node* parent;
	vector<Node*> children;
	string name;
};

map<long long, vector<Node*>>hash_map;

int main()
{
	while (1)
	{
		int m, n;
		cin >> n >> m;

		//两个0表示结束
		if (!n && !m)break;

		//最先祖先的前一个结点
		Node* Before_Root = new Node;
		Before_Root->parent = nullptr;

		Node* CurParent = Before_Root;//这层Depth是-1
		int CurDepth = 0;
		// 读取家族树
		for (int i = 0; i < n; i++)
		{
			string name_line="";		
			while(name_line.empty())
				getline(cin, name_line);

			//计算nameline前有几个空格，找到新行的深度
			int NewlineDepth = 0;
			for (int i = 0; i < name_line.size(); i++)
			{
				if (name_line[i] == ' ')NewlineDepth += 1;
				else
				{
					//更新为名字
					name_line=name_line.substr(i);
					break;
				}
			}
			//根据新行深度，找到新行的parent，并新增子节点

			Node* NewChild = new Node;
			// 如果新行深度小于现在行，由CurParent向上回溯，找到新行的parent并为他新增子节点
			if (NewlineDepth < CurDepth)
			{
				while (NewlineDepth < CurDepth)
				{
					CurParent = CurParent->parent;
					CurDepth--;
				}
			}
			// 如果新行深度等于现在行，CurParent新增子结点
			else if (NewlineDepth == CurDepth)
			{
				;
			}
			// 如果新行深度大于现在行，CurParent更新为现在行，为CurParent新增子节点
			else
			{
				CurParent = CurParent->children[CurParent->children.size() - 1];
				CurDepth++;
			}

			NewChild->name = name_line;
			NewChild->parent = CurParent;

			CurParent->children.push_back(NewChild);

			// 增加子节点时，计算子节点的hash值，并把hash值同结点指针存入map
			long long hash_code = get_hash(NewChild->name);
			if (hash_map.find(hash_code) == hash_map.end())//没找到
			{
				vector<Node*> newcode;
				newcode.push_back(NewChild);
				hash_map.insert({ hash_code,newcode });
			}
			else
				hash_map.find(hash_code)->second.push_back(NewChild);
		}

		// 读取陈述
		// 只用关心1、4、6项
		for (int i = 0; i < m; i++)
		{
			string Name1, item0, item1,relation, item2, Name2;
			cin>> Name1>> item0>> item1>> relation>> item2>> Name2;

			//Name2末尾有一个.
			Name2 = Name2.substr(0, Name2.size() - 1);

			Node* NodeName1 = nullptr , * NodeName2=nullptr;
			long long hash4Name1, hash4Name2;
			hash4Name1 = get_hash(Name1);
			hash4Name2 = get_hash(Name2);

			// 查找Name对应结点
			for (Node*& node : (hash_map.find(hash4Name1)->second))
			{
				if (node->name == Name1)
				{
					NodeName1 = node;
					break;
				}
			}

			for (Node*& node : (hash_map.find(hash4Name2)->second))
			{
				if (node->name == Name2)
				{
					NodeName2 = node;
					break;
				}
			}

			if (relation == "child")
			{
				bool is_child = false;
				for (Node*& node : NodeName2->children)
				{
					if (node->name == NodeName1->name)
					{
						is_child = true;
						break;
					}
				}

				if (is_child)cout << "True" << endl;
				else cout << "False" << endl;
			}
			else if (relation == "ancestor")
			{
				vector<string> ancestors;
				ancestors.push_back(NodeName2->name);

				Node* CurNode=NodeName2;
				while (CurNode->parent->name != Before_Root->name)
				{
					CurNode = CurNode->parent;
					ancestors.push_back(CurNode->name);
				}

				//检查是否在祖先列中
				bool is_ancestor = false;
				for (string& ancestor : ancestors)
				{
					if (ancestor == NodeName1->name)
					{
						is_ancestor = true;
						break;
					}
				}

				if (is_ancestor)cout << "True" << endl;
				else cout << "False" << endl;
			}
			else if (relation == "sibling")
			{
				//检查是否在兄弟列中
				bool is_sibling = false;
				for (Node*& sibling : NodeName2->parent->children)
				{
					if (sibling->name == NodeName1->name)
					{
						is_sibling = true;
						break;
					}
				}

				if (is_sibling)cout << "True" << endl;
				else cout << "False" << endl;
			}
			else if (relation == "parent")
			{
				bool is_parent = false;
				if (NodeName1->name == NodeName2->parent->name)is_parent = true;

				if (is_parent)cout << "True" << endl;
				else cout << "False" << endl;
			}
			else if (relation == "descendant")
			{
				//name1是name2后代，那么name2是name1前代

				vector<string> ancestors_for_name1;
				ancestors_for_name1.push_back(NodeName1->name);

				Node* CurNode = NodeName1;
				while (CurNode->parent->name != Before_Root->name)
				{
					CurNode = CurNode->parent;
					ancestors_for_name1.push_back(CurNode->name);
				}

				//检查name2是否在name1祖先列中
				bool is_desecent = false;
				for (string& ancestor : ancestors_for_name1)
				{
					if (ancestor == NodeName2->name)
					{
						is_desecent = true;
						break;
					}
				}

				if (is_desecent)cout << "True" << endl;
				else cout << "False" << endl;
			}
		}

		//每个测试用例后给出一个空行
		cout << endl;
		hash_map.clear();
	}

	return 0;
}