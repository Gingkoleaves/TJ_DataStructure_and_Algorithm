#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int opp[25][25];//opp[i][j]表示第i天的j的比赛对手 

void Match(vector<int> aths)
{
	if(aths.size()==2){
		opp[1][aths[0]]=aths[1];
		opp[1][aths[1]]=aths[0];
		return;
	}	
	
	int Len=aths.size();
	if(Len%2){
		aths.push_back(0);
		Match(aths);
	}
	else{
		if((Len/2)%2){
			vector<int> aths1,aths2;
			for(int i=0;i<Len-1;i++)
			{
				if(i<Len)aths1.push_back(aths[i]);
				else aths2.push_back(aths[i]);
			}
			Match(aths1);
			// 记录和0配对的 
			vector<int> empty1,empty2; 
			for(int i=1;i<=Len/2 -1;i++)
				empty1.push_back(opp[i][0]);
				
			Match(aths2);
			for(int i=1;i<=Len/2 -1;i++)
				empty2.push_back(opp[i][0]);
			
			// 下面那行 
			int Match_0=0; 
			for(int i=1;i<=Len/2;i++){
				if(empty1[i]==empty2[i])continue;
				
				if(empty1[i]&&empty2[i]){
				opp[i][empty1[i]]=empty2[i];
				opp[i][empty2[i]]=empty1[i];
				}
			}			

			int cnt=1;
			for(int i=Len/2 +1;i<=Len;i++)//天数 
			{
				for(int j=0;j<Len/2;j++){
					if(!(aths1[j]==0&&aths2[(j+cnt)%aths2.size()]==0)){//不能opp[0]=0; 
						opp[i][empty1[j]]=empty2[(j+cnt)%empty2.size()];
						opp[i][empty2[(j+cnt)%empty2.size()]]=empty1[j];
					}
				}
				cnt++;
			} 
		}
		else{//		num/2为偶数 
			vector<int> aths1,aths2;
			for(int i=0;i<Len;i++)
			{
				if(i<Len)aths1.push_back(aths[i]);
				else aths2.push_back(aths[i]);
			}
			Match(aths1);
			Match(aths2);
			
			// 合并
			int cnt=0;
			for(int i=Len/2;i<=Len;i++)//天数 
			{
				for(int j=0;j<aths1.size();j++){
					if(!(aths1[j]==0&&aths2[(j+cnt)%aths2.size()]==0))//不能opp[0]=0; 
						opp[i][aths1[j]]=aths2[(j+cnt)%aths2.size()];
						opp[i][aths2[(j+cnt)%aths2.size()]]=aths1[j];
				}
				cnt++;
			} 
		}
	}
}



int main()
{
	int n=8;
	
	vector<int> v1;
	
	for(int i=1;i<=n;i++)
		v1.push_back(i);
	
	Match(v1);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			cout<<opp[i][j]<<' ';
		cout<<endl;
	}
	
	return 0;
}
