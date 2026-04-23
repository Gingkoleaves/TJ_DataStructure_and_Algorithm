#include <iostream>
#include <queue>
#include <vector>
// 拓扑排序：用队列维护入度为0的点集，邻接表维护图，不用维护visit
// oj不过是因为没有memset 0 in和G 
using namespace std;

// 维护各点的入度
int in[2010];

// 邻接表存储图
vector<int> G[2010];


    bool canFinish(int numCourses, vector<vector<int>>& pres) {
        if(pres.empty())return true;

        queue<int>S;
        int cnt=0;
        
        for(vector<int>& pre:pres)
        {
            // 记录入度和建立图
            in[pre[1]]++;
            G[pre[0]].push_back(pre[1]);
        }

        // 维护入度为空的点集
        for(int i=0;i<numCourses;i++)
        {
            if(in[i]==0){
                S.push(i);
            }
        }

        while(!S.empty())
        {
            int course=S.front();
            S.pop();
            cnt++;
            for(int i:G[course])
            {
                // 正在访问
                if(--in[i]==0)
                {
                    S.push(i);
                }
            }
        }

        return cnt==numCourses;
    }
    
int main()
{
	vector<vector<int>>pres={{0,1}};
	int numC=2;
	cout<<canFinish(numC,pres);
	
	return 0;
 } 
