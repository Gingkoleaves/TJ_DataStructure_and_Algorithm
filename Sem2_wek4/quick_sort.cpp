#include <algorithm> 
#include <vector>
#include <iostream>

using namespace std;
// 双指针快排 ,可以证明，分解问题后l1!=l,r!=r 
void m_quick_sort(vector<int>&stocks,int l,int r)
{
    int mid=(l+r)/2;
    int mid_elem=stocks[mid];

    int l1=l,r1=r;
    // cout<<"start: l:"<<l1<<' '<<"r:"<<r1<<' '<<"mid_elem:"<<mid_elem<<endl;
    while(l1<=r1)
    {
        while(stocks[l1]<mid_elem)l1++;
        // cout<<"while1:l:"<<l1<<' '<<"r:"<<r1<<endl;
        while(stocks[r1]>mid_elem)r1--;
        // cout<<"while2:l:"<<l1<<' '<<"r:"<<r1<<endl;
        
        if(l1<=r1){
        	swap(stocks[l1],stocks[r1]);
        	l1++;
        	r1--;
		} 
        // cout<<"if1:l:"<<l1<<' '<<"r:"<<r1<<endl;
    }
    // cout<<"break"<<endl;
    
    if(l<r1)m_quick_sort(stocks,l,r1);
    if(l1<r)m_quick_sort(stocks,l1,r);
}

// 存首位-快排 :注意要减小问题规模，下次排序不包括base 
void quick_sort2(vector<int>& stocks,int l,int r)
{
	if(l==r)return;	

    int l1=l,r1=r;
    int base=stocks[l1];
    // cout<<"start: l:"<<l1<<' '<<"r:"<<r1<<' '<<endl;
    while(l1<r1)
    {
        while(l1<r1&&stocks[r1]>base)r1--;				
		stocks[l1]=stocks[r1];

		while(l1<r1&&stocks[l1]<=base)l1++;	
		stocks[r1]=stocks[l1]; 
	}
    stocks[l1]=base; 
    
    if(l<r1)quick_sort2(stocks,l,r1-1);
    if(l1<r)quick_sort2(stocks,l1+1,r);
}

void liner_time(vector<int>& stocks,int l,int r,int cnt)
{
	if(l==r)return;	

    int l1=l,r1=r;
    int base=stocks[l1];
    while(l1<r1)
    {
        while(l1<r1&&stocks[r1]>base)r1--;				
		stocks[l1]=stocks[r1];

		while(l1<r1&&stocks[l1]<=base)l1++;	
		stocks[r1]=stocks[l1]; 
	}
    stocks[l1]=base; 
    
    if(l1==cnt) return;
    else if(l1>cnt){
    if(l<r1)liner_time(stocks,l,r1-1,cnt);
	}
	else {
    	if(l1<r)liner_time(stocks,l1+1,r,cnt);
	}
}


int main()
{
	vector<int> v1={1,3,2};
	
	int cnt=3;
	m_quick_sort(v1,0,v1.size()-1);	 
	
	for(int i=0;i<cnt;i++)cout<<v1[i]<<' ';
		
	return 0;
}




