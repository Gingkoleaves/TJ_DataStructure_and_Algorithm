#include <iostream>
#include <vector>

using namespace std;
 
int dp[205][20000];

bool canPartition(vector<int>& nums) {
 	int sum=0;
    for(int i=0;i<nums.size();i++){
    	sum+=nums[i];
    	dp[i][nums[i]]=1;
	}
	if(sum%2)return false;
	
	// 判断能否加和为sum/2 
	for(int i=1;i<nums.size();i++){
		for(int j=sum/2;j>=0;j--){
			if(j>=nums[i])
				dp[i][j]=dp[i-1][j-nums[i]]||dp[i-1][j];
			else	
				dp[i][j]=dp[i-1][j];		
		}
	}
	for(int i=0;i<nums.size();i++){
		for(int j=0;j<=sum/2;j++)
			cout<<dp[i][j]<<' ';
		cout<<endl;
	}
	return dp[nums.size()-1][sum/2];
}
 
 int main()
 {
 	vector<int> v1={2,2,3,5};
 	cout<<canPartition(v1)<<endl;
 	return 0;
 }
