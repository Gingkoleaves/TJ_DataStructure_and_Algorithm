#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int minTimeToInfect(int n, int start, vector<pair<int, int>>& children) {
    // 构建邻接表
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; ++i) {
        int left = children[i].first;
        int right = children[i].second;
        if (left != -1) { // -1表示没有左子节点
            graph[i].push_back(left);
            graph[left].push_back(i); // 添加反向边
        }
        if (right != -1) { // -1表示没有右子节点
            graph[i].push_back(right);
            graph[right].push_back(i); // 添加反向边
        }
    }

    // BFS开始感染
    queue<int> q;
    vector<bool> visited(n, false);

    q.push(start); // 从start节点开始
    visited[start] = true;

    int minutes = 0;

    while (!q.empty()) {
        // 当前层的节点数量
        int size = q.size();

        for (int i = 0; i < size; ++i) {
            int current = q.front();
            q.pop();

            // 遍历所有邻居节点
            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) { // 邻居节点未感染
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // 每处理完一层，时间增加1分钟
        if (!q.empty()) { // 如果还有节点待感染
            minutes++;
        }
    }

    return minutes;
}

int main() {
    int n, start;
    cin >> n >> start;
    vector<pair<int, int>> children(n);

    for (int i = 0; i < n; ++i) {
        cin >> children[i].first >> children[i].second;
    }

    // 计算感染时间
    int result = minTimeToInfect(n, start, children);
    cout << result << endl;

    return 0;
}
