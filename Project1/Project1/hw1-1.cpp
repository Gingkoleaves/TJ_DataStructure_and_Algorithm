#include <iostream>
#define MAX_N 100005
using namespace std;

int nums[MAX_N];
int main()
{
	int n, k;
	cin>>n>>k;
	for (int i = 0; i < n; i++)
		cin>>nums[i];

	int begin = ((n - k) % n);
	begin = begin >= 0 ? begin : begin + n;

	for (int cnt = 0; cnt < n; (++begin) %= n, cnt++)
		cout << nums[begin] << ' ';

	return 0;
}

//%n运算结果范围-(n-1)~+(n-1)，注意会出现负余数/模
//例：-3%7 -3/7==0，所以-3%7==-3 - (-3/7)== -3
//求整数商时，取余向0舍入，取模向负无穷舍入
//取余时，用尽量少的n靠近待取余数