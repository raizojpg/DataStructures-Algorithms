#include <iostream>
#include <vector>

using namespace std;

int n, m;
char x;
char empty_cell = '.';
char val = '*';

int di[4] = { 0,0,1,-1 };
int dj[4] = { -1,1,0,0 };

bool ok(int i, int j) {
    if (i >= 0 && j >= 0 && i < n && j < m) {
        return true;
    }
    return false;
}

void fill(int i, int j,vector<vector<char>>& mat) {
    mat[i][j] = val;
    for (int d = 0; d < 4; d++) {
        int ii = i + di[d];
        int jj = j + dj[d];
        if (ok(ii, jj) && mat[ii][jj] == empty_cell) {
            fill(ii, jj, mat);
        }
    }
}

int main()
{
    cin >> n >> m;
    vector<char> v(m);
    vector<vector<char>> mat(n, v);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    int ct = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == empty_cell) {
                ct++;
                fill(i, j, mat);
            }
        }
    }

    cout << ct;
}
