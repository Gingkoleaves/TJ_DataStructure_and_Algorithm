#include <iostream> 
#include <algorithm>

using namespace std;
int a[20010];
int b[20010];
int cnt=0;

// 用归并排序求逆序对 

void combine(int l,int r)
{
	int mid=(l+r)/2;
	
	int i=l;
	int j=mid+1;
	
	for(int k=l;k<=r;k++)
	{
		if(j>r||(i<=mid&&a[i]<=a[j]))b[k]=a[i++];
		else {
			b[k]=a[j++];
			cnt+=mid-i+1;
		}
	}
	
	for(int i=l;i<=r;i++)
		a[i]=b[i];
}

// 归并排序
void merge_sort(int l,int r)
{
	int mid=(l+r)/2;
	
	if(l==r)return;
	else{
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	}
	
	combine(l,r);	
} 
 

int main()
{
	int n;
	
	while(1)
	{
		cnt=0;
		scanf("%d",&n);
		if(!n)break;
		
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
			
		merge_sort(0,n-1);
		
		cout<<cnt<<endl;
	}
		
	
	return 0;
}
