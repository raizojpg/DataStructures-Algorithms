#include <fstream>
#include <vector>
using namespace std;

ifstream cin("rmq.in");
ofstream cout("rmq.out");

class RMQ { 
    vector<vector<int>> rmq;

    int largestPowerOfTwo(int n) {
        int msb = 0;
        while (n > 1) {
            n >>= 1;
            msb++;
        }
        return msb;
    }

public:

    void Compute(vector<int>& vec) {
        int k = 0;
        rmq.push_back(vec);
        while (1 << (k + 1) <= vec.size()) {
            vector<int> v;
            v.push_back(0);
            for (int i = 1; i + (1 << k) < rmq[k].size(); i++) {
                v.push_back(min(rmq[k][i], rmq[k][i + (1 << k)]));
            }
            rmq.push_back(v);
            k++;
        }
    }

    int Response(int x, int y) {
        int k = largestPowerOfTwo(y - x + 1);
        return min(rmq[k][x], rmq[k][y - (1 << k) + 1]);
    }

    void Print(int k) {
        for (int i = 0; i < rmq.size(); i++) {
            for (int j = 1; j < rmq[i].size(); j++) {
                cout << rmq[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

};


int main()
{
    RMQ rmq;
    int n, k;
    cin >> n >> k;
    vector<int> vec(n+1,0);

    for (int i = 1; i <= n; i++) {
        cin >> vec[i];
    }

    rmq.Compute(vec);

    int x, y;
    for (int i = 0; i < k; i++) {
        cin >> x >> y;
        cout << rmq.Response(x, y) << endl;
    }

}