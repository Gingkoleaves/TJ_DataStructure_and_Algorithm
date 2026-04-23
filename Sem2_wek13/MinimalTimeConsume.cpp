#include <iostream> 
#include <vector>
#include <numeric> 
#include <algorithm>
// 问题可能是run作为数组传入accumulate不合法，在oj上不能正常运行
// run改为vector就可以了 
using namespace std;
bool cmp(vector<int> t1,vector<int> t2)
{
    return t1[1]<t2[1];
}
int run[2005];
int findMinimumTime(vector<vector<int>>& tasks) {
    sort(tasks.begin(),tasks.end(),cmp);
    int ans=0;
    for(vector<int> t:tasks)
    {
        int residue=t[2]-accumulate(run+t[0],run+t[1]+1,0);

        for(int i=t[1];residue>0;i--){
            if(run[i]==0){
                run[i]=1;
                residue--;
                ans++;
            }                
        }
    }
    return ans;
}
    
int main()
{
	vector<vector<int>> ve1={{1,3,2},{2,5,3},{5,6,2}};
	cout<<findMinimumTime(ve1);
	
	
	return 0;
}
