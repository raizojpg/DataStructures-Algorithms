#include <vector>

class DisjointSet {
private:
    std::vector<int> set;
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