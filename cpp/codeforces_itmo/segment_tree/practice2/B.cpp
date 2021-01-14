#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class SegmentTree {

    vector<long long> a;
    vector<long long> tree;
    int n;
    long long NEUTRAL = 0;

    void expand(vector<long long> &a) {
        n = a.size();
        n = pow(2, ceil(log2(n)));
        this->a.resize(n, 0);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, NEUTRAL);
    }

    void build(int lx, int rx, int v) {
        if (lx == rx) {
            tree[v] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(lx, m, 2 * v + 1);
        build(m + 1, rx, 2 * v + 2);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    void invert(int i, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            tree[v] = tree[v] == 1 ? 0 : 1;
            return;
        }
        if (i < lx || i > rx) {
            return;
        }
        int m = (lx + rx) / 2;
        invert(i, lx, m, 2 * v + 1);
        invert(i, m + 1, rx, 2 * v + 2);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    int query(int k, int lx, int rx, int v) {
        if (lx == rx) {
            return lx;
        }
        int m = (lx + rx) / 2;
        if (k < tree[2 * v + 1]) {
            return query(k, lx, m, 2 * v + 1);
        }
        return query(k - tree[2 * v + 1], m + 1, rx, 2 * v + 2);

    }

public:

    SegmentTree(vector<long long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    void invert(int i) {
        invert(i, 0, n - 1, 0);
    }

    int query(int k) {
        return query(k, 0, n - 1, 0);
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < m; i++) {
        int operation, value;
        cin >> operation >> value;
        if (operation == 1) {
            tree.invert(value);
        } else if (operation == 2) {
            cout << tree.query(value) << endl;
        }
    }

    return 0;
}