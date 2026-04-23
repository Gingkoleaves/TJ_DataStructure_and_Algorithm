// 搜索串：逐个元素搜索,阶段结果存入parital_ans，在partial_ans的基础上不断后缀添加新的回文串 
// 动态规划预处理回文串

#include <vector>

class Solution {
public:
    int is_rs[20][20];
    vector<vector<string>> ans;
    vector<string> partial_ans;

    void search(string s,int start)
    {
        int n=s.size();

        if(start==n)
        {
            ans.push_back(partial_ans);
            return ;
        }

        // 枚举右侧指针
        for(int end=start;end<n;end++)
        {
            if(is_rs[start][end]){
                partial_ans.push_back(s.substr(start,end-start+1));
                search(s,end+1);
                partial_ans.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int n=s.length();
        memset(is_rs,1,sizeof(is_rs));

        for(int i=n-1;i>=0;i--)
        {
            for(int j=i+1;j<n;j++)
            {
                is_rs[i][j]=(s[i]==s[j])&&is_rs[i+1][j-1];
            }
        }

        search(s,0);
        return ans;
    }
};
