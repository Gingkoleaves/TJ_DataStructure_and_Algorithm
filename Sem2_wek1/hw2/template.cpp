/**
 * @file    template.cpp
 * @name    模板程序
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
#include <algorithm>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
string ss[110];
bool comp(string s1,string s2)
{
	return s1+s2 >s2+s1; 
}

class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        // 这里填写你的代码 
        int leng=nums.size();
        for(int i=0;i<leng;i++)
        	ss[i]=to_string(nums[i]);
        	
        sort(ss,ss+leng,comp);
		
		string res;
		for(int i=0;i<leng;i++)
			res+=ss[i];
			
		return res;
    }
};
