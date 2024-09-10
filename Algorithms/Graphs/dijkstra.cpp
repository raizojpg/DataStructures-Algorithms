#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream cin("dijkstra.in");
ofstream cout("dijkstra.out");

struct nd {
    int node;
    int distance;
};

int n, m, x, y, cost, start;

vector<int> dijkstra(vector<vector<pair<int, int>>>& list, int start) {
    
    struct compareFuncPairMin {
        bool operator()(nd a, nd  b) const {
            return a.distance > b.distance;
        }
    };

    priority_queue<nd, vector<nd>, compareFuncPairMin> heap;
    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, 0);
    vector<int> visited(n + 1, 0);
 
    dist[start] = 0;
    heap.push({start,dist[start]});
    
    while (!heap.empty()) {
        nd current = heap.top();
        heap.pop();
        if (visited[current.node] == 0) {
            visited[current.node] = 1;
            for (auto& e : list[current.node]) {
                if (dist[e.first] == -1 || current.distance + e.second < dist[e.first]) {
                    dist[e.first] = current.distance + e.second;
                    parent[e.first] = current.node;
                    heap.push({ e.first,dist[e.first] });
                }
            }
        }
    }
    return dist;
}


int main()
{
    cin >> n >> m >> start;
    vector<vector<pair<int, int>>> list(n+1);

    for (int i = 0; i < m;i++) {
        cin >> x >> y >> cost;
        list[x].push_back({ y,cost });
        list[y].push_back({ x,cost });
    }

    vector<int> dist = dijkstra(list, start);

    for (int i = 1; i < dist.size(); i++) {
        cout << dist[i] << " ";
    }

}
