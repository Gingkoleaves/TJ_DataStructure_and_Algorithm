#include <iostream>
#include <algorithm>
#include <vector>
int tail[10000];
using namespace std;
 
	int lengthOfLIS(vector<int>& nums) {
       if(nums.empty())return 0;

        int len=1;
        tail[0]=nums[0];//tail[i]表示长度为i+1的递增子序列的最小末尾值
        for(int i=1;i<nums.size();i++){
            // 找第一个pos使得nums[i]<=tail[pos]
            if(nums[i]>tail[len-1]){
                tail[len++]=nums[i];
                
                for(int i=0;i<len;i++)
                	{
                		cout<<tail[i]<<' ';
					}
					cout<<endl;
            }
            else{
                int left=0,right=len-1;
                while(left<right){
                    int mid=(left+right)/2;
                    if(tail[mid]>=nums[i]){
                        right=mid;
                    }else{
                        left=mid+1;
                    }
                }
                tail[right]=nums[i];
                
                for(int i=0;i<len;i++)
                	{
                		cout<<tail[i]<<' ';
					}
					cout<<endl;
                
            }
        }
        return len;
    }
    
int main()
{
	vector<int>v1={10,9,2,5,3,7,101,18};
	cout<<lengthOfLIS(v1)<<endl;;
	return 0;
}
