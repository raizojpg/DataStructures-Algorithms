#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
using namespace std;

ifstream cin("maxflow.in");
ofstream cout("maxflow.out");

int n, m, x, y, c;

void dfs(int current, int flow, map<int, map<int, int>>& residual, vector<int>& path, int& sink_flow, int sink = n) {
    if (current == sink) {
        sink_flow = flow;
    }
    else {
        for (auto item : residual[current]) {
            int next = item.first;
            int val = item.second;

            if (path[next] == -1 && val != 0) {
                path[next] = current;
                int new_flow = min(flow, val);
                dfs(next, new_flow, residual, path, sink_flow);
                if (sink_flow != 0) { break; }
                path[next] = -1;
            }
        }
    }
}

void bfs(map<int, map<int, int>>& residual, vector<int>& path, int& sink_flow, int source = 1, int sink = n) {
    queue<pair<int, int>> q;
    q.push({ source, INT_MAX });

    while (!q.empty()) {
        int current = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (auto item : residual[current]) {
            int next = item.first;
            int val = item.second;
            if (path[next] == -1 && val != 0) {
                path[next] = current;
                int new_flow = min(flow, val);
                if (next == sink) {
                    sink_flow = new_flow;
                    return;
                }
                q.push({ next, new_flow });
            }
        }
    }
}

int maxflow(map<int, map<int, int>>& residual, int source = 1, int sink = n) {
    int result = 0;
    while (true) {
        int flow = 0;
        vector<int> path(n + 1, -1);
        path[source] = 0;
        
        //dfs(source, INT_MAX, residual, path, flow);  // Ford-Fulkerson
        bfs(residual, path, flow);                     // Edmond-Karp
        if (!flow) { break; }

        result += flow;
        int current = sink;
        while (current != source) {
            int prev = path[current];
            residual[prev][current] -= flow;
            residual[current][prev] += flow;
            current = prev;
        }
    }
    return result;
}

int main()
{
    cin >> n >> m;
    map<int, int> aux;
    map<int,map<int, int>> residual;

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        auto it = residual[x].find(y);
        if (it == residual[x].end()) {
            residual[x][y] = c;
            residual[y][x] = 0;
        }
        else {
            residual[x][y] = c;
        }
    }

    int result = maxflow(residual);

    cout << result << endl;
}