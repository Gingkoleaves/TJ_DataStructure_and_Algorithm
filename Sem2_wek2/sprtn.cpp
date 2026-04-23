#include <stdio.h>
using namespace std;

int my_sqrt(int n)
{
	int l=1,r=n-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(mid*mid==n) return mid;
		else if(mid*mid>n) r=mid-1;
		else l=mid+1;
	}
	return l-1;

}


int main() 
{
	int n; 
	scanf("%d",&n);
	
	printf("%d",my_sqrt(n));
	return 0;
}
