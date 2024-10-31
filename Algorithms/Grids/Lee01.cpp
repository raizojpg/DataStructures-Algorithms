#include <fstream>
#include <vector>
#include <deque>
#include <climits>
using namespace std;

ifstream cin("padure.in");
ofstream cout("padure.out");

int n, m, is, js, ifin, jfin;
int di[4] = { 0,0,1,-1 };
int dj[4] = { -1,1,0,0 };

bool ok(int i, int j) {
    if (i > 0 && j > 0 && i <= n && j <= m) {
        return true;
    }
    return false;
}

int lee(vector<vector<int>>& mat, int is = 1, int js = 1, int ifin = n, int jfin = m) {
    vector<int> d(m + 1, INT_MAX);
    vector<vector<int>> distances(n + 1, d);
    deque<pair<int, int>> dq;
    dq.push_front({ is,js });
    distances[is][js] = 0;

    while(!dq.empty()){
        int i = dq.front().first;
        int j = dq.front().second;
        dq.pop_front();

        if (i == ifin && j == jfin) { continue; }

        for (int d = 0; d < 4; d++) {
            int ii = i + di[d];
            int jj = j + dj[d];

            if (ok(ii, jj)) {
                if (mat[ii][jj] == mat[i][j] && distances[ii][jj] > distances[i][j]) {
                    distances[ii][jj] = distances[i][j];
                    dq.push_front({ ii,jj });
                }
                else if (mat[ii][jj] != mat[i][j] && distances[ii][jj] > distances[i][j] + 1) {
                    distances[ii][jj] = distances[i][j] + 1;
                    dq.push_back({ ii,jj });
                }
            }
        }
    } 
    return distances[ifin][jfin];
}

int main()
{
    cin >> n >> m >> is >> js >> ifin >>  jfin;
    vector<int> v(m+1);
    vector<vector<int>> mat(n+1, v);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }

    int res = lee(mat, is, js, ifin, jfin);
    cout << res;
}
