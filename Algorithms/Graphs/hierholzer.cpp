#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

ifstream cin("ciclueuler.in");
ofstream cout("ciclueuler.out");

int n, m, x, y;

vector<int> hierholzer(vector<vector<int>>& list, vector<pair<int,int>>& edges, vector<int>& degrees, int start = 1) {
    
    for (int degree : degrees) {
        if (degree % 2 != 0) {
            return { -1 };
        }
    }
    
    vector<int> visited(m);
    vector<int> euler;
    stack<int> path;
    path.push(start);
    while (!path.empty()) {
        
        int node = path.top();
        if (list[node].empty()) {
            euler.push_back(node);
            path.pop();
        }
        else {
            bool pushed = false;
            while (!list[node].empty() && !pushed) {
                int edge_index = list[node].back();
                list[node].pop_back();

                if (visited[edge_index] == 0) {
                    visited[edge_index] = 1;
                    int next = node ^ edges[edge_index].first ^ edges[edge_index].second;
                    path.push(next);
                    pushed = true;
                }
            }
        }
    }
    return euler;
}


int main()
{
    cin >> n >> m;
    vector<vector<int>> list(n + 1);
    vector<pair<int, int>> edges(m);
    vector<int> degrees(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        list[x].push_back(i);
        list[y].push_back(i);
        edges[i] = { x,y };
        degrees[x]++;
        degrees[y]++;
    }

    vector<int> euler_cicle = hierholzer(list, edges, degrees);

    if (euler_cicle[0] == -1) { cout << "-1" << endl; }
    else {
        for (int i = 0; i < euler_cicle.size() - 1; i++) {
            cout << euler_cicle[i] << " ";
        }
        cout << endl;
    }
}