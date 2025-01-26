#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

ifstream cin("critical.in");
ofstream cout("critical.out");

int n, m, x, y, k;

struct criticals {
    vector<pair<int, int>> edges;
    set<int> nodes;
    set<set<int>> biconex;
};

struct node_info {
    struct level {
        int current;
        int min;
    }lvl;
    bool visited;
    int parent;
};

void critical_dfs(int current, vector<vector<int>>& list, vector<node_info>& nodes, stack<int>& path ,criticals& result) {
    nodes[current].visited = 1;
    path.push(current);
    for (int& node : list[current]) {
        if (nodes[node].visited == 0) {
            nodes[node].parent = current;
            nodes[node].lvl.current = nodes[current].lvl.current + 1;
            nodes[node].lvl.min = nodes[current].lvl.current + 1;
            critical_dfs(node, list, nodes, path, result);
            
            if (nodes[current].lvl.current < nodes[node].lvl.min) {
                result.edges.push_back({ current,node });
            }
            if (nodes[current].lvl.current <= nodes[node].lvl.min && nodes[current].parent != 0 ) {
                result.nodes.insert(current);
                
                set<int> bi;
                while (path.top() != node) {
                    bi.insert(path.top());
                    path.pop();
                }
                bi.insert(path.top());
                path.pop();
                bi.insert(current);
                result.biconex.insert(bi);
            }

            nodes[current].lvl.min = min(nodes[current].lvl.min, nodes[node].lvl.min);
        }
        else if (nodes[current].parent != node) {
            nodes[current].lvl.min = min(nodes[current].lvl.min, nodes[node].lvl.current);
        }

    }

}

criticals critical(vector<vector<int>>& list, int root = 1){
    
    bool is_root_critical = false;
    
    vector<node_info> nodes(n + 1);
    criticals result;
    nodes[root].visited = 1;
    stack<int> path;
    path.push(root);

    for (int i = 0; i < list[root].size();i++) {
        int node = list[root][i];
        if (nodes[node].visited == 0) {
            nodes[node].parent = root;
            nodes[node].lvl.current = 1;
            nodes[node].lvl.min = 1;
            critical_dfs(node, list, nodes, path, result);

            if (nodes[root].lvl.current < nodes[node].lvl.min) {
                result.edges.push_back({ root,node });
            }

            if (i != 0) {
                is_root_critical = true; 
                set<int> bi;
                while (path.top() != node) {
                    bi.insert(path.top());
                    path.pop();
                }
                bi.insert(path.top());
                path.pop();
                bi.insert(root);
                result.biconex.insert(bi);
            }
        }
    }

    if (is_root_critical) {result.nodes.insert(root); }

    set<int> bi;
    while (!path.empty()) {
        bi.insert(path.top());
        path.pop();
    }
    result.biconex.insert(bi);

    return result;
    
}

int main()
{

    cin >> n >> m;
    vector<vector<int>> list(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list[x].push_back(y);
        list[y].push_back(x);
    }

    for (auto& vec : list) {
        sort(vec.begin(), vec.end());
    }

    criticals result = critical(list);
        
}