#include <iostream>
#include <algorithm>

using namespace std;
#define OFFSET 5000000
char vis[10000010];
int num[3010];
// 桶排序尝试 

int main()
{
	int n;
	scanf("%d",&n);
	
	int elem,cnt=0;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&elem);
		
		if(vis[OFFSET+elem]==0){
			num[cnt++]=elem;
		}
		vis[OFFSET+elem]++;
	}
	
	sort(num,num+cnt);
	
	int l=0;	
	while(num[l]<0){
		int r=cnt-1;
		for(;num[r]>0;r--){
			// cout<<"consider: "<<num[l]<<" & "<<num[r]<<endl;
			int diff=-(num[l]+num[r]);
			if(diff>num[r]||diff<num[l])				
				continue;
						
			vis[OFFSET+num[l]]--;
			vis[OFFSET+num[r]]--;
			
			if(vis[OFFSET+diff])
				printf("%d %d %d\n",num[l],-(num[l]+num[r]),num[r]);				
				// 这里从小到大 
			vis[OFFSET+num[l]]++;
			vis[OFFSET+num[r]]++;
						
		}	
		l++;	
	}
		
	
		
	return 0;
} 
