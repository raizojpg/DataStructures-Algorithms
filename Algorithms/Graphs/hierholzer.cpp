#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ifstream cin("euler.in");
ofstream cout("euler.out");

int n, m, x, y;

vector<int> hierholzer(vector<vector<pair<int, int>>>& list, vector<int>& degrees, int start = 1) {

    for (int degree : degrees) {
        if (degree % 2 != 0) {
            return { -1 };
        }
    }

    vector<int> euler;
    stack<int> path;
    path.push(start);
    while (!path.empty()) {

        int node = path.top();
        if (!list[node].empty()) {
            int size = list[node].size();
            pair<int, int> edge = list[node][size - 1];
            pair<int, int> reverse_edge = { edge.second,edge.first };

            int next = edge.second;
            path.push(next);

            list[node].erase(list[node].begin() + size - 1);
            for (int i = 0; i < list[next].size(); i++) {
                if (list[next][i] == reverse_edge) {
                    list[next].erase(list[next].begin() + i);
                    break;
                }
            }
        }
        else {
            euler.push_back(node);
            path.pop();
        }
    }
    return euler;
}


int main()
{
    cin >> n;
    vector<vector<pair<int, int>>> list(n + 1);
    vector<int> degrees(n + 1);

    while (cin >> x >> y) {
        list[x].push_back({ x,y });
        list[y].push_back({ y,x });
        degrees[x]++;
        degrees[y]++;
    }

    vector<int> euler_cicle = hierholzer(list, degrees);

    cout << euler_cicle.size() << endl;
    for (int i = 0; i < euler_cicle.size(); i++) {
        cout << euler_cicle[i] << " ";
    }
    cout << endl;

}