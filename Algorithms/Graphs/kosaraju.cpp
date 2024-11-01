#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

ifstream cin("ctc.in");
ofstream cout("ctc.out");

int n, m, x, y;

void dfs(int current, vector<vector<int>>& list, vector<int>& visited, vector<int>& path) {
    visited[current] = 1;
    for (int node : list[current]) {
        if (visited[node] == 0) {
            dfs(node, list, visited, path);
        }
    }
    path.push_back(current);
}

vector<int> tarjan_toposort(vector<vector<int>>& list) {
    vector<int> toposort;
    vector<int> visited(n + 1);

    for (int i = 1; i < list.size(); i++) {
        if (visited[i] == 0) {
            dfs(i, list, visited, toposort);
        }
    }

    reverse(toposort.begin(), toposort.end());
    return toposort;
}

vector<vector<int>> kosaraju(vector<vector<int>>& list, vector<vector<int>>& list_inv){
    vector<vector<int>> result;

    vector<int> toposort = tarjan_toposort(list);

    vector<int> visited(n + 1);
    for(int node: toposort){
        if (visited[node] == 0) {
            vector<int> scc;
            dfs(node, list_inv, visited, scc);
            result.push_back(scc);
        }        
    }
    return result;
}

int main()
{
    cin >> n >> m;
    vector<vector<int>> list(n + 1);
    vector<vector<int>> list_inv(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list[x].push_back(y);
        list_inv[y].push_back(x);
    }

    vector<vector<int>> result = kosaraju(list, list_inv);

    cout << result.size() << endl;
    for (int i = 0; i < result.size();  i++) {
        for (int& node : result[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}
