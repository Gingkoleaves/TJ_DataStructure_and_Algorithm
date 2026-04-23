#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void cal_bee_num(long long int& female, long long int& male,int n)
{
	for (int i = 0; i < n; i++)
	{
		long long int mid = female;
		female = male + 1;
		male += mid;
	}
}

int main()
{
	int n = 0;
	while (scanf("%d", &n) &&n!= -1)
	{
		long long int female = 1,male=0;
		cal_bee_num(female, male, n);
		printf("%lld %lld\n", male, male + female);
	}


	return 0;
}