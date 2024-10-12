#include <fstream>
#include <vector>
using namespace std;

ifstream cin("rmq.in");
ofstream cout("rmq.out");

class RMQ_2D {
    vector<vector<vector<int>>> rmq;

    int largestPowerOfTwo(int n) {
        int msb = 0;
        while (n > 1) {
            n >>= 1;
            msb++;
        }
        return msb;
    }

public:

    void Compute(vector<vector<int>>& mat) {
        rmq.push_back(mat);
        int k = 0;
        while ((1 << (k + 1)) <= mat.size()) {
            vector<vector<int>>vec;
            vector<int> v;
            v.push_back(0);
            vec.push_back(v);

            for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
                vector<int> v;
                v.push_back(0);

                for (int j = 1; j + (1 << k) < rmq[k][i].size(); j++) {
                    int maxi1 = max(rmq[k][i][j], rmq[k][i + (1 << k)][j]);
                    int maxi2 = max(rmq[k][i][j + (1 << k)], rmq[k][i + (1 << k)][j + (1 << k)]);
                    int maxi = max(maxi1, maxi2);
                    v.push_back(maxi);
                }
                vec.push_back(v);
            }
            rmq.push_back(vec);
            k++;
        }
    }

    int Response(int x, int y, int l) {
        int k = largestPowerOfTwo(l);
        int maxi1 = max(rmq[k][x][y], rmq[k][x + l - (1 << k)][y]);
        int maxi2 = max(rmq[k][x][y + l - (1 << k)], rmq[k][x + l - (1 << k)][y + l - (1 << k)]);
        int maxi = max(maxi1, maxi2);
        return maxi;
    }

    void Print(int k) {
        for (int i = 0; i < rmq[k].size(); i++) {
            for (int j = 1; j < rmq[k][i].size(); j++) {
                cout << rmq[k][i][j] << " ";
            }
            cout << endl;
        }
    }

};


int main()
{
    RMQ_2D rmq;
    int n, k;
    cin >> n >> k;
    vector<int> v(n+1,0);
    vector<vector<int>> mat(n+1,v);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mat[i][j];
        }
    }

    rmq.Compute(mat);

    int x, y, l;
    for (int i = 0; i < k; i++) {
        cin >> x >> y >> l;
        cout << rmq.Response(x, y, l) << endl;
    }

}