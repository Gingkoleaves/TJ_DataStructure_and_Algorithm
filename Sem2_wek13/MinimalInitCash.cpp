
class Solution {
public:
// 应当考虑花费cost最多的方法
// 考虑“亏损最大时刻”，不妨设为T：T一定出现在先全部亏损交易，再全部盈利交易的安排下；T一定在一次交易的中间(已经cost没有得到cache back时)
// T时刻，如果还有亏损交易未进行，把他放到T前会得到更大的亏损；如果已经进行了盈利，放到T后面会得到更大的亏损
// 此时，T要么在最后一个亏损的中间状态，要么在第一个盈利的中间阶段：前者总亏损是
// cashbackj+sigma (costi-cashbacki),后者总亏损是costk+sigma (costi-cashbacki)，逐个选择j、k比较即可
    long long minimumMoney(vector<vector<int>>& transactions) {
        long long Total_lose=0;
        int max_add=INT_MIN;
        for(vector<int> tr:transactions)
        {
            int& cost=tr[0];
            int& back=tr[1];
            if(cost>back){
                max_add=max(max_add,back);
                Total_lose+= cost-back;
            }
            else{
                max_add=max(max_add,cost);
            }
        }
        return max_add+Total_lose;
    }
};
