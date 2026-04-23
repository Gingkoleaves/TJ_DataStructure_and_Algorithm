// 搜索树：将解空间视为树来搜索
class Solution {
public:
    double res=24;

    bool same(double d1,double d2)
    {
        return abs(d1-d2)<1e-2;
    }

    // 在partial_ans的基础上产生结果
    bool solve(vector<double> partial_ans)
    {
        int len=partial_ans.size();
        if(len==0)return false;
        if(len==1)return same(partial_ans[0],24);

        for(int i=0;i<len;i++)
        {
            for(int j=0;j<len;j++)
            {
                if(i!=j)
                {
                    double d1=partial_ans[i],d2=partial_ans[j];
                    bool ans=false;
                    vector<double> ar2=partial_ans;

                    int k=max(i,j),s=min(i,j);
                    ar2.erase(ar2.begin()+k);
                    ar2.erase(ar2.begin()+s);
                    
                    ar2.push_back(d1+d2);
                    ans=solve(ar2)||ans;
                    ar2.pop_back();
                    
                    ar2.push_back(d1-d2);
                    ans=solve(ar2)||ans;
                    ar2.pop_back();
                    
                    ar2.push_back(d1*d2);
                    ans=solve(ar2)||ans;
                    ar2.pop_back();
                    
                    ar2.push_back(d1/d2);
                    ans=solve(ar2)||ans;
                    ar2.pop_back();

                    if(ans)return true;
                }
            }
        }
        return false;
    };

    bool judgePoint24(vector<int>& cards) {
        vector<double> c;
        for(int i:cards)
            c.push_back(double(i));
        return solve(c);
    };
};
