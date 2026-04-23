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

class Solution {
public:
    vector<int> inventoryManagement(vector<int>& stock, int cnt) 
    {
        vector<int> v1;
        liner_time(stock,0,stock.size()-1,cnt);	 
        
        for(int i=0;i<cnt;i++)
            v1.push_back(stock[i]);
        
        return v1;
    }
};
