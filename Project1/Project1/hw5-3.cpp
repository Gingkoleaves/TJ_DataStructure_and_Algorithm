/**
 * @file    template.cpp
 * @name    p138模板程序
 * @date    2022-11-20
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;


/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
public:
    int solve(std::vector<vector<std::string>>& old_chart,
        std::vector<std::vector<std::string>>& new_chart) {
        // 这里填写你的代码
        int n = old_chart.size();
        int m = old_chart[0].size();

        int nodes = n *m;
        int rings = 0;

        //遍历表寻找交换环:一定有环，但个数不确定
        map<string,int> ocm;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ocm.insert({ old_chart[i][j], i *m+j });
            }
        }

        vector<int> visited(n * m, 0);

        for (int i = 0; i <n; i++) {
            for (int j = 0; j < m; j++) 
            {
                int start_pos = i * m + j;
                string want_find = old_chart[i][j];
                if(visited[(ocm.find(want_find))->second] != -1)
                while (1)
                {
                    //old_chart中对应位置
                    int ncp=(ocm.find(want_find))->second;

                    //同位置的newchart
                    string nc = new_chart[ncp / m][ncp % m];

                    //old_chart中这个new中字符的位置
                    int ocp = (ocm.find(nc))->second;

                    visited[ncp] = -1;//表示已经被访问过

                    if (ocp == start_pos)//找到环了
                    {
                        rings++;
                        break;
                    }

                    //该位置的oldchart
                    want_find = old_chart[ocp / m][ocp % m];
                }
            }
        }
        
        return nodes - rings;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/
//
//int main() {
//    int n, m;
//    std::cin >> n >> m;
//    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
//    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            std::cin >> old_chart[i][j];
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            std::cin >> new_chart[i][j];
//        }
//    }
//
//    Solution s;
//    std::cout << s.solve(old_chart, new_chart) << std::endl;
//    return true;
//}
