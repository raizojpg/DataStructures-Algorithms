#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

ifstream cin("sortaret.in");
ofstream cout("sortaret.out");

int n, m, x, y;

void tarjan_dfs(vector<vector<int>>& list, vector<int>& visited, int current, vector<int>& toposort) {
    visited[current] = 1;
    for (int node : list[current]) {
        if (visited[node] == 0) {
            tarjan_dfs(list, visited, node, toposort);
        }
    }
    toposort.push_back(current);
}

vector<int> tarjan(vector<vector<int>>& list) {
    vector<int> toposort;
    vector<int> visited(n + 1);

    for (int i = 1; i < list.size(); i++) {
        if (visited[i] == 0) {
            tarjan_dfs(list, visited, i, toposort);
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

    vector<int> toposort = tarjan(list);

    for (int& node : toposort) {
        cout << node << " ";
    }
    cout << endl;

}
