#include <fstream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

ifstream cin("sortaret.in");
ofstream cout("sortaret.out");

int n, m, x, y;

vector<int> kahn(vector<vector<int>>& list_out, vector<set<int>>& list_in) {
    vector<int> toposort;
    vector<int> visited(n + 1);
    stack<int> s;

    for (int i = 1; i < list_in.size(); i++) {
        if (list_in[i].empty()) {
            s.push(i);
            visited[i] = 1;
        }
    }

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        toposort.push_back(current);
        
        for (int node : list_out[current]) {
            if (visited[node] == 0) {
                list_in[node].erase(current);
                if (list_in[node].empty()) {
                    s.push(node);
                    visited[node] = 1;
                }
            }
        }
    }
    return toposort;
}

int main()
{
    cin >> n >> m;
    vector<vector<int>> list_out(n + 1);
    vector<set<int>> list_in(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list_out[x].push_back(y);
        list_in[y].insert(x);
    }

    vector<int> toposort = kahn(list_out,list_in);

    for (int& node : toposort) {
        cout << node << " ";
    }
    cout << endl;

}
