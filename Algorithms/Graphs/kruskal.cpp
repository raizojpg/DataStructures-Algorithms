#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream cin("apm.in");
ofstream cout("apm.out");

class DisjointSet {
private:
    vector<int> set;
public:
    DisjointSet(int size) : set{vector<int>(size, -1)}{}

    int Find(int x) {
        while (set[x] >= 0) {
            int parent = set[x];
            if (set[parent] >= 0) {
                set[x] = set[parent];
            }
            x = parent;
        }
        return x;
    }

    void Union(int x, int y) {
        int rootx = Find(x);
        int rooty = Find(y);

        if (set[rootx] < set[rooty]) { // add y to x
            set[rootx] += set[rooty];
            set[rooty] = rootx;
        }
        else { // add x to y
            set[rooty] += set[rootx];
            set[rootx] = rooty;
        }
    }

    int size(int x) {
        x = Find(x);
        return -set[x];
    }

};

struct edge {
    int x;
    int y;
    int cost;
};

int n, m, x, y, cost, sum;

bool compare_edge(edge& a, edge& b) {
    return a.cost < b.cost;
}

vector<edge> kruskal(vector<edge>& edges) {

    DisjointSet set(n + 1);
    vector<edge> msp;

    sort(edges.begin(), edges.end(), compare_edge);
    
    for (auto& edge : edges) {
        if (set.Find(edge.x) != set.Find(edge.y)) {
            set.Union(edge.x, edge.y);
            msp.push_back(edge);
            sum += edge.cost;
        }
    }

    return msp;
}

int main()
{
    cin >> n >> m;
    vector<edge> edges;

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> cost;
        edges.push_back({ x,y,cost });
    }

    vector<edge> msp = kruskal(edges);

    cout << sum << endl;
    cout << msp.size() << endl;
    for (auto& edge : msp) {
        cout << edge.x << " " << edge.y << endl;
    }
   
}
