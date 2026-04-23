#include <iostream>
#include <vector>


using namespace std;

void merge(vector<int>& B,vector<int>& C,vector<int>& A)
{
	int i=0,j=0,k=0;
	int lenB=B.size(),lenC=C.size();
	while(i<lenB||j<lenC)
	{		
		if(i<lenB&&j<lenC)
		{		
		if(B[i]>C[j])
			A.push_back(C[j++]);
		else
			A.push_back(B[i++]);
		}
		
		if(i>=lenB)
			while(j<lenC)
				A.push_back(C[j++]);
		
		if(j>=lenC)
			while(i<lenB)
				A.push_back(B[i++]);		
	}
}



int main()
{
	vector<int>B={1,2,4,5,7,9};
	vector<int>C={3,5,7,8,9,11};
	vector<int>A;
	
	merge(B,C,A);
	
	for(int i=0;i<A.size();i++)
		cout<<A[i]<<' ';
	cout<<endl; 
	return 0;
	
} 
