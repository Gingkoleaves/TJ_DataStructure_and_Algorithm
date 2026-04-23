#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        
    }
};

 

void pr_Per(vector<int> a,int l)
{
    if(l>=a.size())return;
    
    printf("%d",a[l]);
    pr_Per(a,l+1);
    printf("\n");

    for(int i=l+1;i<a.size();i++)
    {
        swap(a[i],a[l]);
        pr_Per(a,l+1);
    	printf("\n");
    }
}



int main()
{
	int n;
	scanf("%d",&n);
	
	vector<int> a;
	
	for(int i=0;i<n;i++)
		a.push_back(i+1);
			
	pr_Per(a,0);
	return 0;
}
