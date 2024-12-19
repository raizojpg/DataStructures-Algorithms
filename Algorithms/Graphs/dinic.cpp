#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
using namespace std;

ifstream cin("maxflow.in");
ofstream cout("maxflow.out");

int n, m, x, y, c;


void dfs(int current, int flow, map<int, map<int, int>>& residual, vector<int>& level, vector<int>& path, int& sink_flow, int sink = n) {
    if (current == sink) {
        sink_flow = flow;
    }
    else {
        for (auto item : residual[current]) {
            int next = item.first;
            int val = item.second;
            
            if (level[next] == level[current] + 1 && path[next] == -1 && val != 0) {
                    path[next] = current;
                    int new_flow = min(flow, val);
                   
                    dfs(next, new_flow, residual, level, path, sink_flow);
                    if (sink_flow != 0) { break; }
                    
                    path[next] = -1;
                    level[next] = -1; //Prune dead ends
            }    
        }
    }
}

void bfs(map<int, map<int, int>>& residual, vector<int>& level, int source = 1, int sink = n) {
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto item : residual[current]) {
            int next = item.first;
            int val = item.second;
            
            if (level[next] == -1 && val != 0) {
                level[next] = level[current] + 1;
                q.push(next);
            }
        }
    }
}

int dinic(map<int, map<int, int>>& residual, int source = 1, int sink = n) {
    int result = 0;
    while (true) {
        vector<int> level(n + 1, -1);
        
        bfs(residual, level); // Build level graph
        if (level[sink] == -1) { break; }

        while (true) {
            vector<int> path(n + 1, -1);
            path[source] = 0;
            int flow = 0;

            dfs(source, INT_MAX, residual, level, path, flow);  // Get augumented path
            if (flow == 0) { break; }

            result += flow;
            int current = sink;
            while (current != source) {
                int prev = path[current];
                residual[prev][current] -= flow;
                residual[current][prev] += flow;
                current = prev;
            }  
        }
    }
    return result;
}

int main()
{
    cin >> n >> m;
    map<int, int> aux;
    map<int, map<int, int>> residual;

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

    int result = dinic(residual);

    cout << result << endl;
}