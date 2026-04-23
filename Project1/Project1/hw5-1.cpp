#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define Seq_Maxlen 1005
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;

	int nums[Seq_Maxlen];
	int queries[Seq_Maxlen];
	int answers[Seq_Maxlen];
		
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	for (int i = 0; i < m; i++)
		cin >> queries[i];

	sort(nums,nums+n);
	int sum[Seq_Maxlen] = { 0 };

	for (int i = 0; i < n; i++)
		sum[i + 1] = sum[i] + nums[i];

	for (int i = 0; i < m; i++)
		answers[i] = (upper_bound(sum+1, sum +1+ n, queries[i])-(sum+1));
	

	for (int i = 0; i < m; i++)
		cout << answers[i] << ' ';

	return 0;
}