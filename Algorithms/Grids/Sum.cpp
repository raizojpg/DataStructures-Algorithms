#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
int is, js, ii, jj;
int mat_sum;

int main() {

    cin >> n >> m >> k;
    vector<int> v(m+1, 0);
    vector<vector<int>> mat(n+1, v);
    vector<vector<int>> sum(n+1, v);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++){
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        cin >> is >> js >> ii >> jj;
        mat_sum = sum[ii][jj] - sum[is - 1][jj] - sum[ii][js - 1] + sum[is - 1][js - 1];
        cout << mat_sum << endl;
    }

}