#include <fstream>
#include <vector>
#include <climits>
using namespace std;

ifstream cin("royfloyd.in");
ofstream cout("royfloyd.out");

int n, m, x, y, cost;

vector<vector<int>> roy_floyd_warshall(vector<vector<pair<int, int>>>& list) {
	vector<int> d(n + 1, INT_MAX);
	vector<int> v(n + 1, 0);
	vector<vector<int>> dist(n + 1, d);
	vector<vector<int>> next(n + 1, v);

	for (int i = 1; i < n + 1; i++) {
		dist[i][i] = 0;
		for (auto node : list[i]) {
			dist[i][node.first] = node.second;
			next[i][node.first] = node.first;
		}
	}
	
	for (int k = 1; k < n + 1; k++) {
		for (int i = 1; i < n + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
					if (dist[i][j] > dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
					}
				}
			}
		}
	}

	return dist;
}

int main()
{

	cin >> n >> m;
	vector<vector<pair<int, int>>> list(n + 1);

	for (int i = 0; i < m; i++) {
		cin >> x >> y >> cost;
		list[x].push_back({ y,cost });
		list[y].push_back({ x,cost });
	}

	vector<vector<int>> dist = roy_floyd_warshall(list);

	bool ok = true;  //check for negative cycle
	
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (i == j && dist[i][j] != 0) { ok = false; }
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	if (!ok) { cout << "Negative cycle" << endl; }

}
