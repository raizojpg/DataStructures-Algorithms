#include <fstream>
#include <deque>
#include <vector>
#include <climits>
using namespace std;

ifstream cin("camionas.in");
ofstream cout("camionas.out");

int n, m, x, y, r, resistence;

vector<int> bfs01(vector<vector<pair<int, int>>>& list, int start = 1) {
    vector<int> distances(n + 1, INT_MAX);
    deque<int> dq;
    dq.push_back(start);
    distances[start] = 0;
    
    while (!dq.empty()) {
        int current = dq.front();
        dq.pop_front();

        for (int i = 0; i < list[current].size(); i++) {
            int node = list[current][i].first;
            int w = list[current][i].second;
            int dist = distances[current] + w;
            
            if (distances[node] > dist) {
                distances[node] = dist;
                if (w == 0) {dq.push_front(node);}
                else {dq.push_back(node);}
            }
        }
    }
    return distances;
}

int main()
{
    cin >> n >> m >> r;
    vector<vector<pair<int, int>>> list(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> resistence;
        if (resistence < r) {resistence = 1;}
        else {resistence = 0;}
        list[x].push_back({ y,resistence });
        list[y].push_back({ x,resistence });
    }

    vector<int> distances = bfs01(list);

    cout << distances[n];

}
