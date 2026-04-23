/**
 * @file    template.cpp
 * @name    p57模板程序
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <chrono>
using namespace std;
int b[100000];

void combine(vector<int>& a,int l,int r)
{
	int mid=(l+r)/2;
	
	int i=l;
	int j=mid+1;
	
	for(int k=l;k<=r;k++)
	{
		if(j>r||(i<=mid&&a[i]<=a[j]))b[k]=a[i++];
		else {
			b[k]=a[j++];
			// cnt+=mid-i+1;
		}			
	}
	
	
	for(int i=l;i<=r;i++)
		a[i]=b[i];	
	
	
}

// �鲢����
void merge_sort(vector<int>& a,int l,int r)
{
	int mid=(l+r)/2;
	
	if(l==r)return;
	else{
	merge_sort(a,l,mid);
	merge_sort(a,mid+1,r);
	}
	
	combine(a,l,r);	
} 
 

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
public:
    std::vector<int> mySort(std::vector<int> &nums) {
        // 这里填写你的代码
		merge_sort(nums,0,nums.size()-1);
		return nums;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
	
    int n;
    std::cin >> n;
    
	//auto start = chrono::high_resolution_clock::now();
	
    std::vector<int> nums(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> nums[i];
    }
    Solution s;
    std::vector<int> after_sort(s.mySort(nums));
    std::cout << after_sort[0];
    for (int i = 1; i < n; i ++) {
        std::cout << ' ' << after_sort[i];
    }
    std::cout << std::endl;    
    
    
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	
    //cout<<"����ʱ��(��s)��"<<duration.count()<<"***"<<endl; 
    return 0;
}
