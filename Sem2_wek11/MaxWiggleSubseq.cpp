// 1. 重新开始的长度为1
// 2. 更新状态时，可以考虑上一次的相反状态+1，也可以直接是上一次同状态 

// 题解：
/*
下面以 up[i] 为例，说明其状态转移规则：
当 nums[i]≤nums[i-1] 时，我们无法选出更长的「上升摆动序列」的方案。因为对于任何以 nums[i] 结尾的「上升摆动序列」，我们都可以将 nums[i] 替换为 nums[i-1]，使其成为以 nums[i-1] 结尾的「上升摆动序列」。
当 nums[i]>nums[i-1] 时，我们既可以从 up[i-1] 进行转移，也可以从 down[i-1] 进行转移。下面我们证明从 down[i-1] 转移是必然合法的，即必然存在一个 down[i-1] 对应的最长的「下降摆动序列」的末尾元素小于 nums[i]。
我们记这个末尾元素在原序列中的下标为 j，假设从 j 往前的第一个「谷」为 nums[k]，我们总可以让 j 移动到 k，使得这个最长的「下降摆动序列」的末尾元素为「谷」。
然后我们可以证明在这个末尾元素为「谷」的情况下，这个末尾元素必然是从 nums[i] 往前的第一个「谷」。证明非常简单，我们使用反证法，如果这个末尾元素不是从 nums[i] 往前的第一个「谷」，那么我们总可以在末尾元素和 nums[i] 之间取得一对「峰」与「谷」，接在这个「下降摆动序列」后，使其更长。
这样我们知道必然存在一个 down[i-1] 对应的最长的「下降摆动序列」的末尾元素为 nums[i] 往前的第一个「谷」。这个「谷」必然小于 nums[i]。证毕。
这样我们可以用同样的方法说明 down[i] 的状态转移规则，最终的状态转移方程为：
  
up[i]={ 
up[i-1], nums[i]<=nums[i-1]
max(up[i-1],down[i-1]+1),nums[i]>nums[i-1]
   
down[i]={ 
down[-1],nums[i]≥nums[i-1]
max(up[i-1]+1,down[i-1]),nums[i]<nums[i-1]

可以改进为
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return n;
        }
        int up = 1, down = 1;
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                up = down + 1;
            } else if (nums[i] < nums[i - 1]) {
                down = up + 1;
            }
        }
        return max(up, down);
    }

*/ 
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int state[1050][2]; 
        // state[i][0]表示以i结尾的，i的上一个数大于i的最长摆动子序列长度
        // state[i][1]表示以i结尾的，i的上一个数小于i的最长摆动子序列长度
        state[0][0]=1;
        state[0][1]=1;
        for(int i=1;i<nums.size();i++)
        {
            int j=i-1;
            while(j>=0&&nums[j]<=nums[i])j--;
            if(j==-1){
                state[i][1]=1;
            }
            else{                
                state[i][1]=state[j][0]+1;
                state[i][1]=max(state[j][1],state[i][1]);
            }

            j=i-1;
            while(j>=0&&nums[j]>=nums[i])j--;
            if(j==-1){
                state[i][0]=1;
            }
            else{                
                state[i][0]=state[j][1]+1;
                state[i][0]=max(state[j][0],state[i][0]);
            }

        }

        int max_cnt=1;
        for(int i=1;i<nums.size();i++){
            max_cnt=max(max_cnt,state[i][0]);
            max_cnt=max(max_cnt,state[i][1]);
        }

        return max_cnt;
    }
};
