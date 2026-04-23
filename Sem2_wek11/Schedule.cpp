bool cmp(vector<int>& v1,vector<int>& v2){
    if(v1[1]==v2[1])return v1[0]<v2[0];
    return v1[1]<v2[1];
}

// 可以后悔的贪心
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(),courses.end(),cmp);
        int cnt=0;
        int totalConsume=0;
        priority_queue<int> pq; // 最大堆


        for(int i=0;i<courses.size();i++)
        {
            int limitation=courses[i][1];
            int duration=courses[i][0];
            if(duration+totalConsume<=limitation){
                cnt++;
                totalConsume+=duration;
                pq.push(duration);
            }else if(!pq.empty()&&pq.top()>duration){
                totalConsume -= pq.top();
                pq.pop();
                totalConsume += duration;
                pq.push(duration);
            }
        }

        return cnt;
    }
};
