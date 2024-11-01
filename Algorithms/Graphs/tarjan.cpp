#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

ifstream cin("sortaret.in");
ofstream cout("sortaret.out");

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

int main()
{
    cin >> n >> m;
    vector<vector<int>> list(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list[x].push_back(y);
    }

    vector<int> toposort = tarjan_toposort(list);

    for (int& node : toposort) {
        cout << node << " ";
    }
    cout << endl;

}
