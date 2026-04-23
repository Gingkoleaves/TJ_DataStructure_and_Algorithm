#include <iostream>
#include <algorithm>

struct card{
	int value;
	int num;
}cards[1000];

using namespace std;

int dp[1000];// 前i物品能否组成和j 
bool cmp(struct card c1,struct card c2)
{
	return c1.value>c2.value;
}

// 贪心不能最优：6、5、4、3、3，贪心差值3，最优解差值1 
// 01背包 
int dpp(int n)
{
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=cards[i].value;
	}
	
	dp[0]=1;
	
	// 原地dp
	for(int i=0;i<n;i++)
		for(int j=sum/2;j>=cards[i].value;j--)
			if(dp[j-cards[i].value])dp[j]=1;
	
	int ans1=sum;
	
	for(int j=sum/2;j>=0;j--)
		if(dp[j]) return ans1=j;
	
	return ans1;
}

int main()
{
	int n;
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		scanf("%d",&cards[i].value);
		cards[i].num=i;
	}
	
	int ans1=dpp(n);
	
	cout<<ans1<<endl;

 } 
 
/*
8
2 1 3 1 5 2 3 4
*/
