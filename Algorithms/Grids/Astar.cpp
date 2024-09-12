#include <fstream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

ifstream cin("astar.in");
ofstream cout("astar.out");

int n;
int di[4] = { 0,0,1,-1 };
int dj[4] = { -1,1,0,0 };

void print(vector<pair<int, int>>& vec) {
	for (auto& p : vec) {
		cout << p.first << " " << p.second << endl;
	}
	cout << endl;
}

void print(vector<vector<char>>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[0].size(); j++) {
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check(int i, int j) {
	if (i >= 0 && j >= 0 && i < n && j < n) {
		return true;
	}
	return false;
}

float euclidian_distance(int i, int j, int ii, int jj) {
	return sqrt((ii - i) * (ii - i) + (jj - j) * (jj - j));
}

void clear_path(vector<vector<char>>& grid, vector<pair<int, int>>& path) {
	if (path.size() != 0) {
		int step = '0';
		for (int h = 0; h < path.size() - 1; h++) {
			int i = path[h].first;
			int j = path[h].second;
			if (grid[i][j] != step) {
				path.erase(path.begin() + h);
				grid[i][j] = '.';
				h--;
			}
			else {
				bool ok = false;
				for (int d = 0; d < 4; d++) {
					int ii = i + di[d];
					int jj = j + dj[d];
					if (check(ii, jj) && grid[ii][jj] == step + 1) {
						ok = true; break;
					}
				}
				if (ok) { step++; }
				else {
					path.erase(path.begin() + h);
					grid[i][j] = '.';
					h--;
				}
			}
		}
	}
}

vector<pair<int, int>> astar(vector<vector<char>> grid, int is, int js, int ifin, int jfin) {

	struct node {
		int i, j;
		int step;
		float score;
	};

	struct compareFuncPairMin {
		bool operator()(node a, node b) const {
			return a.score > b.score;
		}
	};

	priority_queue<node, vector<node>, compareFuncPairMin> heap;
	vector<pair<int, int>> path;

	if (grid[is][js] == '.' && grid[ifin][jfin] == '.') {
		heap.push({ is,js,0,euclidian_distance(is,js,ifin,jfin) });

		while (!heap.empty()) {
			node current = heap.top();
			heap.pop();
			int i = current.i;
			int j = current.j;
			grid[i][j] = '0' + current.step;
			path.push_back({ i,j });
			if (i == ifin && j == jfin) { break; }
			
			for (int d = 0; d < 4; d++) {
				int ii = i + di[d];
				int jj = j + dj[d];
				if (check(ii, jj) && grid[ii][jj] == '.') {
					heap.push({ ii,jj,current.step+1,euclidian_distance(ii,jj,ifin,jfin) });
				}
			}
		}
	}
	clear_path(grid, path);
	print(grid);

	return path;
}

int main()
{
	cin >> n;
	vector<char> g(n);
	vector<vector<char>> grid(n, g);
	char x;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> x;
			grid[i][j] = x;
		}
	}

	int i, j, ii, jj, q;
	cin >> q;
	for(int h=0;h<q;h++){
		cin >> i >> j >> ii >> jj;
		cout << i << " " << j << " - " << ii << " " << jj << endl;
		vector<pair<int, int>> path = astar(grid, i, j, ii, jj);
		cout << int(path.size()) - 1 << endl;
		print(path);
	}

}


