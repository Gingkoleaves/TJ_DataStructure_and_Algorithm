#include <iostream>
#include <queue>
#include <set>
#include <algorithm>

// 优先队列comp是后面比前面为真，comp(后,前)==tRue 
// 因为没有清空pq导致错误 

using namespace std;
short a[110][2010];

struct Seq{
	int sum;
	vector<short> seq_index;
};

struct Comp {
    bool operator()(Seq sq1,Seq sq2){
	return sq1.sum>sq2.sum;
}
};

priority_queue<Seq,vector<Seq>,Comp> pq;
vector<int> result; // 存储结果
set<vector<short>> seen; // 用于去重

int main()
{
	int T,m,n;
	scanf("%d",&T);
	
	for(int i=0;i<T;i++)
	{
		scanf("%d%d",&m,&n);
		for(int j=0;j<m;j++)
		{
			for(int k=0;k<n;k++)
				scanf("%hd",&a[j][k]);
			sort(a[j],a[j]+n);// 复杂度 m*nlogn 
		}				
				
		// 优先队列
		int initSum=0;
		for(int i=0;i<m;i++)
			initSum+=a[i][0];
			
		vector<short> initIndex(m,0);			
		Seq initSeq={initSum,initIndex};
		pq.push(initSeq);		
	
	    while (result.size() < n && !pq.empty()) {
			Seq sq= pq.top();
	        pq.pop();
	
			int currentSum=sq.sum;
			vector<short> indices=sq.seq_index;
	
	        // 如果当前索引组合已经处理过，跳过
	        if (seen.count(indices)) continue;
	        seen.insert(indices);
	
	        // 将当前和加入结果
	        result.push_back(currentSum);
    		if (result.size() >= n) break;
	        
	        //cout<<"Sum="<<currentSum<<", Seq=";
	        //for(int i=0;i<m;i++)
	        //cout<<a[i][indices[i]]<<' ';
	        //cout<<endl;
	
	        // 尝试替换每个序列的当前元素
	        for (int i = 0; i < m; ++i) {
	            if (indices[i] + 1 < n) {
	                vector<short> newIndices = indices;
	                newIndices[i] += 1; // 将第i个序列的索引加1
	                int newSum = currentSum - a[i][indices[i]] + a[i][newIndices[i]];
	            	pq.push({newSum,newIndices});
	            	
	            	//cout<<"NewSum="<<newSum<<", NewSeq=";
	        		//for(int i=0;i<m;i++)
	        		// cout<<a[i][newIndices[i]]<<' ';
	        		//cout<<endl;
				}
	        }
	    }	    
	    
	    for(int i=0;i<n;i++)
	    	cout<<result[i]<<' ';
	    cout<<endl;

		while(!pq.empty())pq.pop();
		result.clear();
		seen.clear();
	}
	return 0;
} 

