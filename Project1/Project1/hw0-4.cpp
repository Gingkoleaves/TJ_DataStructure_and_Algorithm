#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;


int main()
{
	queue<int> circle;
	int n, m;
	scanf("%d%d", &n, &m);
	//初始化
	for (int i = 0; i <= n; i++)
		circle.push(i);

	//排队杀人
	while (circle.size() > 1)
	{
		int mid;
		for (int i = 0; i < 2; i++) {
			mid = circle.front();
			circle.pop();
			circle.push(mid);
		}
		circle.pop();
	}
	printf("%d", circle.front());


	return 0;
}