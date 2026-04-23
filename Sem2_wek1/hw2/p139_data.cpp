/**
 * @file    p139.cpp
 * @name    p139样例程序
 * @date    2022-11-22
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>


class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<std::string> list(n);
        for( int i = 0; i < n; i ++ )
            list[i] = std::to_string(nums[i]);
        auto comp = [](const std::string &s1, const std::string &s2) {
            int n1 = s1.length(), n2 = s2.length();
            for( int i = 0; i < n1 + n2; i ++ ) {
                char c1 = (i < n1 ? s1[i] : s2[i - n1]);
                char c2 = (i < n2 ? s2[i] : s1[i - n2]);
                if( c1 != c2 )
                    return c1 > c2;
            }
            return false;
        };
        std::sort(list.begin(), list.end(), comp);
        std::string ans;
        for( int i = 0; i < n; i ++ ) {
            ans += list[i];
        }
        int i = 0;
        while( i < ans.length() - 1 && ans[i] == '0' )
            i ++;
        return ans.substr(i);
    }
};

/**
 * @brief   随机洗牌
*/
void shuffle(std::vector<int> &list, int size = 0) {
    if( size <= 0 )
        size = list.size();
    else
        list.resize(size);
    
    for( int i = 0; i < size; i ++ )
        list[i] = i;
    for( int i = size - 1; i > 0; i -- ) {
        int j   = rand() % (i + 1);
        int t   = list[i];
        list[i] = list[j];
        list[j] = t;
    }
}

int main()
{
    int exp10[10];
    exp10[0] = 1;
    for (int i = 0; i < 9; i ++ ) {
        exp10[i + 1] = exp10[i] * 10;
    }
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n;
        if( index <= test_num * 0.2 ) {
            n = rand() % 6 + 5;
        }
        else if( index <= test_num * 0.4 ) {
            n = rand() % 6 + 55;
        }
        else {
            n = rand() % 11 + 90;
        }

        // 文件输出代码
        std::vector<int> nums(n);
        std::vector<int> indexs;
        shuffle(indexs, n);

        for (int i = 0; i < n; i ++ ) {
            if( i < n - 1 && rand() % 3 == 0 ) {
                int l1 = rand() % 7;
                nums[i] = rand() % exp10[8 - l1] + 1;
                nums[i + 1] = nums[i] * exp10[l1 + 1] + rand() % (exp10[l1 + 1] - exp10[l1]) + exp10[l1];
                i++;
            }
            else {
                nums[i] = rand() % 1000000000 + 1;
            }
        }
        fin << n << '\n' << nums[indexs[0]];
        for (int i = 1; i < n; i ++ ) {
            fin << ' ' << nums[indexs[i]];
        }
        fin << std::endl;
        Solution s;
        fout << s.largestNumber(nums) << std::endl;
        fin.close();
        fout.close();
    }
}
