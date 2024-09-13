#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream cin("bellmanford.in");
ofstream cout("bellmanford.out");

int n, m, x, y, cost, start;

vector<int> bellman_ford(vector<vector<pair<int, int>>>& list, int start) {

    queue<int> q;
    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, 0);
    vector<int> in_queue(n + 1, 0);
    vector<int> nr_of_visits(n + 1, 0);

    dist[start] = 0;
    q.push(start);
    in_queue[start] = 1;
    nr_of_visits[start] = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        in_queue[current] = 0;
        
        for (auto& e : list[current]) {
            int node = e.first; 
            if (dist[current] + e.second < dist[node]) {
                dist[node] = dist[current] + e.second;
                parent[node] = current;
                
                if (in_queue[node] == 0) {
                    in_queue[node] = 1;
                    q.push(node);
                    nr_of_visits[node]++;
                    if (nr_of_visits[node] > list.size()) { //cycle
                        dist[0] = INT_MIN;
                        return dist;
                    }
                }
            }
        }
    }
    return dist;
}


int main()
{
    cin >> n >> m >> start;
    vector<vector<pair<int, int>>> list(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> cost;
        list[x].push_back({ y,cost });
    }

    vector<int> dist = bellman_ford(list, start);

    if (dist[0] == INT_MIN) {
        cout << "Negative cycle" << endl;
    }
    else {
        for (int i = 1; i < dist.size(); i++) {
            cout << dist[i] << " ";
        }
    }

}