#include <fstream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

ifstream cin("sortaret.in");
ofstream cout("sortaret.out");

int n, m, x, y;

vector<int> kahn(vector<vector<int>>& list, vector<int>& grade_in) {
    vector<int> toposort;
    stack<int> s;

    for (int i = 1; i < grade_in.size(); i++) {
        if (grade_in[i] == 0) {
            s.push(i);
        }
    }

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        toposort.push_back(current);

        for (int node : list[current]) {
            grade_in[node]--;
            if (grade_in[node] == 0) {
                s.push(node);
            }
        }
    }
    return toposort;
}

int main()
{
    cin >> n >> m;
    vector<vector<int>> list(n + 1);
    vector<int> grade_in(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list[x].push_back(y);
        grade_in[y]++;
    }

    vector<int> toposort = kahn(list, grade_in);

    for (int& node : toposort) {
        cout << node << " ";
    }
    cout << endl;

}
