#include <iostream>
#include <cmath>

using namespace std;
// 动态规划：遍历解空间 
int ps[10005];

bool is_square(int num)
{
	double rot=sqrt(num);
	int rod_i=rot;
	
	if(rod_i*rod_i==num)
		return true;
	else
		return false;	
}

int find_ps(int num)
{	
	int min_cnt=10000;
	 
	// 递归出口 
	if(num<=4 ||ps[num]!=0)
		return ps[num];		
		
	if(is_square(num))
	{
		ps[num]=1;
	}
	else{
		for(int i=1;i<=num/2;i++)
		{
			int j=num-i;
			min_cnt=min(min_cnt,find_ps(i)+find_ps(j));
		}
		ps[num]=min_cnt;
	}
	
	return ps[num];
} 

int main()
{
	int n;
	scanf("%d",&n);
	
	// 初始化 
	ps[0]=0;
	ps[1]=1;
	ps[2]=2;
	ps[3]=3;
	ps[4]=1;
	
	cout<<find_ps(n)<<endl;
	
	return 0;
}
