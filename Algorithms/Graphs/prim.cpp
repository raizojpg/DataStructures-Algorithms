#include <fstream>
#include <queue>
#include <vector>
using namespace std;

ifstream cin("apm.in");
ofstream cout("apm.out");

struct edge{
    int x;
    int y;
    int cost;
};

int n, m, x, y, cost, sum;

vector<edge> prim(vector<vector<pair<int, int>>>& list) {
    
    struct compareFuncPairMin {
        bool operator()(edge a, edge b) const {
            return a.cost > b.cost;
        }
    };

    priority_queue<edge, vector<edge>, compareFuncPairMin> heap;
    vector<edge> msp;

    vector<int> visited(list.size());
    visited[0] = 1; //count how many were visited
    visited[1] = 1;
    for (auto& e : list[1]) {
        heap.push({ 1,e.first,e.second });
    }

    while (visited[0] != n) {
        auto edge = heap.top();
        heap.pop();

        if (visited[edge.y] == 0) {
            visited[0]++;
            visited[edge.y] = 1;
            sum += edge.cost;
            msp.push_back(edge);

            for (auto& e : list[edge.y]) {
                heap.push({ edge.y,e.first,e.second });
            }
        }
    }
    return msp;
}


int main()
{
    cin >> n >> m;
    vector<vector<pair<int,int>>> list(n+1);
    
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> cost;
        list[x].push_back({ y,cost });
        list[y].push_back({ x,cost });
    }

    vector<edge> msp = prim(list);

    cout << sum << endl;
    cout << msp.size() << endl;
    for (auto& edge : msp) {
        cout << edge.x << " " << edge.y << endl;
    }

}
