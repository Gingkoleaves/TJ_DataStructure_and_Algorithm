#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

//¸ø³östring£¬¼ÆËãvalue
int cal_value(string src)
{
	int score=0;
	for (int i = 0; i < src.length()&&i<255; i++)
	{
		int char_value = 0;
		if (src[i] == ' ');
		else {
			char_value = src[i] - 'A' + 1;
		}
		score += (i+1) * char_value;
	}

	return score;
}

int main()
{	
	string s1;
	vector<int> value;
	int cnt = 0;
	while (getline(cin, s1)) {
		if (s1=="#") {
			break;
		}
		else {
			value.push_back(cal_value(s1));
		}
	}

	for (int cnt=0;cnt<value.size();cnt++)
	{
		printf("%d", value[cnt]);
		if (cnt != value.size() - 1)
			printf("\n");

	}


	return 0;
}