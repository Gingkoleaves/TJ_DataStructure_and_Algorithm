#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 找一个区间，对k个列表中的每一个列表，区间至少包括其中的一个元素
// 考虑每个元素的该区间大小，应该从中选出一个最小区间
// 对任意元素，该区间的大小由所有K个列表中大于等于该元素的最小的元素决定 

// 不会
// 注意有负数，maxvalue不能设为0初始值 

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int left=0,right=INT_MAX;
        int size=nums.size();
        vector<int> next(size);

        auto cmp = [&nums, &next](int m, int n) {
            return nums[m][next[m]] > nums[n][next[n]];
        };
        int maxvalue=INT_MIN;
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        
        // 初始化堆：将每个列表的第一个元素入堆
        for (int i = 0; i < size; i++) {
            if (!nums[i].empty()) {              // 检查空列表
                pq.push(i);
                maxvalue = max(maxvalue, nums[i][0]);
            }
        }

        while(true)
        {
            int row=pq.top();
            pq.pop();
            int minvalue=nums[row][next[row]];
            if(maxvalue-minvalue<right-left){
                left=minvalue;
                right=maxvalue;
            }
            if(next[row]==nums[row].size()-1){
                break;
            }
            ++next[row];
            maxvalue=max(maxvalue,nums[row][next[row]]);
            pq.emplace(row);

        }

        return {right,left};
    }
};
