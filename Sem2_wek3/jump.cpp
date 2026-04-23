#include <iostream>
#include <cstring> // 包含 memset 的头文件

using namespace std; 

class Solution {
public:
    int pos[110]={0};
    Solution(){
        pos[0]=1;
        pos[1]=1;
        pos[2]=2;
    }

    int trainWays(int num) {
        if(num<=2)return pos[num];
        else if(pos[num]!=0) return pos[num];
        pos[num]=(trainWays(num-1)+trainWays(num-2))%1000000007;
        return pos[num];
    }
};
