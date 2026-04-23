#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
	double inc[12];
	for (int i = 0; i < 12; i++)
	{
		scanf("%lf", &inc[i]);
	}

	double ave_inc = 0;
	for (double i : inc)
	{
		ave_inc += i;
	}
	ave_inc /= 12;

	printf("¥%.2f", ave_inc);
	return 0;
}
