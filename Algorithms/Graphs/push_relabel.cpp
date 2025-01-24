#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
using namespace std;

ifstream cin("maxflow.in");
ofstream cout("maxflow.out");

int n, m, x, y, c;

struct edge {
    int capacity;
    int flow;
    int residual;
};

struct node {
    int excess_flow;
    int height;
};

void relabel(map<int, map<int, edge>>& mat, vector<node>& nodes, int node) {
    int mini = INT_MAX;
    for (auto& item : mat[node]) {
        int next = item.first;
        edge& current = item.second;
        if (current.residual > 0) {
            mini = min(mini, nodes[next].height);
        }
    }
    nodes[node].height = mini + 1;
}

void push(map<int, map<int, edge>>& mat, vector<node>& nodes, int node, int next) {
    edge& current = mat[node][next];
    edge& reverse = mat[next][node];

    int pushed_flow = min(current.residual, nodes[node].excess_flow);

    current.flow += pushed_flow;
    reverse.flow -= pushed_flow;

    current.residual = current.capacity - current.flow;
    reverse.residual = reverse.capacity - reverse.flow;

    nodes[next].excess_flow += pushed_flow;
    nodes[node].excess_flow -= pushed_flow;
}

int maxflow(map<int, map<int, edge>>& mat, int source = 1, int sink = n) {

    queue<int> q;
    vector<node> nodes(n + 1, { 0,0 });
    
    nodes[source].height = n;
    nodes[source].excess_flow = INT_MAX;
    for (auto& item : mat[source]) {
        int next = item.first;
        push(mat, nodes, source, next);
        q.push(next);
    }

    while (!q.empty()) {
        int node = q.front();

        for (auto& item : mat[node]) {
            int next = item.first;
            edge& current = item.second;

            if (nodes[node].excess_flow <= 0) { break; }

            if (current.residual > 0 && nodes[node].height > nodes[next].height) {
                push(mat, nodes, node, next);
                if (next != source && next != sink) {
                    q.push(next);
                }
            }
        }

        if (nodes[node].excess_flow > 0) {
            relabel(mat, nodes, node);
        }
        else { q.pop(); }
    }

    return nodes[sink].excess_flow;
}

int main()
{
    cin >> n >> m;
    map<int, map<int, edge>> mat;

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        auto it = mat[x].find(y);
        if (it == mat[x].end()) {
            mat[x][y].capacity = c;
            mat[x][y].residual = c;

            mat[y][x].capacity = 0;
            mat[y][x].residual = 0;
        }
        else {
            mat[x][y].capacity = c;
            mat[x][y].residual = c;
        }
    }

    int result = maxflow(mat);

    cout << result << endl;
}