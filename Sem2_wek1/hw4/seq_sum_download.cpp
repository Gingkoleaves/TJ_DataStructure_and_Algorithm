#include <iostream>
#include <cmath>
#include<queue>
#include <stack>
#include <stdio.h>
#include<cstring>
#include <algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
const int inf=0x3f3f3f3f;
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> pp;
const int N=2010;

int m,n,a[N],b[N],c[N];
void mer()//合并
{
    priority_queue<pp, vector<pp>, greater<pp> > heap;
    for(int i = 0;i < n; i++)heap.push({a[0] + b[i], 0});
    for(int i = 0;i < n; i++)
    {
        pp t=heap.top();
        heap.pop();
        int s=t.first,p=t.second;
        c[i]=s;
        heap.push({s - a[p] + a[p+1], p+1});
    }
    for(int i = 0; i < n; i++) a[i]=c[i];
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        scanf("%d%d",&m,&n);
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        sort(a,a+n);
        for(int i = 0; i < m-1; i++)
        {
            for(int j = 0; j < n; j++)
            scanf("%d",&b[j]);
            mer();
        }
        for(int i = 0; i < n; i++)
            printf("%d " ,a[i]);
        cout<<endl;
    }
    return 0;
}

// 如果MLE，考虑分步作答，而不是一次求出最终结果
// 这里考虑将最优解转化为每新出现的序列和已有序列的组合
// a总是保存已经输入的序列的n个最优解，因为可以证明，新出现的最优解的前N-1元素一定在已有的最优解中 
