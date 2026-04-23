#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 输入一系列字符串，要求输出字典序最大的排列 

string ss[110];
bool comp(string s1,string s2)
{
	return s1+s2 >s2+s1; 
}

int main()
{
	int n;
	scanf("%d",&n);
	
	for(int i=0;i<n;i++)
	{
		cin>>ss[i];
	}
	
	sort(ss,ss+n,comp);
	
	for(int i=0;i<n;i++)
		cout<<ss[i];
		
		cout<<endl;
	return 0;
 } 
