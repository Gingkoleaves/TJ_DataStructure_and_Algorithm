#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
    // 有限的出口，通过递归不稳定地减小问题规模
    int longestSubstring(string s, int k) {
        int vis[200] = {0};
        if (s.length() < k)
            return 0;
        for (char c : s)
            vis[c]++; // 记录每个字符出现次数
        // cout<<s<<' '<<s.length()<<' '<<vis[s[0]]<<endl;
        int i = 0;
        while (i < s.length() && vis[s[i]] >= k) {
            // cout<<i<<' '<<s.length()<<' '<<vis[s[i]]<<endl;
            i++;
        }
        if (i == s.length())
            return s.length();
        int l = longestSubstring(s.substr(0, i), k);
        while (i < s.length() && vis[s[i]] < k)
            i++;
        // cout<<"i="<<i<<endl;
        int r = 0;
        if (i < s.length())
            r = longestSubstring(s.substr(i), k);
        return max(l, r);
    }
};

