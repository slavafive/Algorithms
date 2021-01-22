#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {

    vector<int> a, tree;
    vector<bool> zeros;
    int n;
    int NEUTRAL = INT32_MIN;

    void update(int v) {
        tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void build(int lx, int rx, int v) {
        if (lx == rx) {
            tree[v] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(lx, m, 2 * v + 1);
        build(m + 1, rx, 2 * v + 2);
        update(v);
    }

    int destroy(int l, int r, int power, int lx, int rx, int v) {
        if (l <= lx || rx <= r) {
            zeros[v] = true;
        }
    }

    void set(int i, int value, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            tree[v] = value;
            return;
        }
        if (i < lx || rx < i) {
            return;
        }
        int m = (lx + rx) / 2;
        set(i, value, lx, m, 2 * v + 1);
        set(i, value, m + 1, rx, 2 * v + 2);
        update(v);
    }

public:

    SegmentTree(vector<int> &a) {
        n = pow(2, ceil(log2(a.size())));
        this->a.resize(n, NEUTRAL);
        for (int i = 0; i < n; i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, NEUTRAL);
        zeros.resize(2 * n - 1, false);
        build(0, n - 1, 0);
    }

};

int main() {

    return 0;
}
