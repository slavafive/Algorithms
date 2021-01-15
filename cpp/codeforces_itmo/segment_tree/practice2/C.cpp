#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class SegmentTree {

    vector<long long> a;
    vector<long long> tree;
    int n;
    long long NEUTRAL = INT32_MAX;

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
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
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
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }

    int query(int value, int lx, int rx, int v) {
        if (lx == rx) {
            return lx;
        }
        int m = (lx + rx) / 2;
        if (tree[2 * v + 1] >= value) {
            return query(value, lx, m, 2 * v + 1);
        } else if (tree[2 * v + 2] >= value) {
            return query(value, m + 1, rx, 2 * v + 2);
        }
        return -1;
    }

public:

    SegmentTree(vector<long long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    void set(int i, int value) {
        set(i, value, 0, n - 1, 0);
    }

    int query(int value) {
        if (tree.size() == 1) {
            return tree[0] >= value ? 0 : -1;
        }
        return query(value, 0, n - 1, 0);
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
        cin >> operation;
        if (operation == 1) {
            int i, v;
            cin >> i >> v;
            tree.set(i, v);
        } else if (operation == 2) {
            int x;
            cin >> x;
            cout << tree.query(x) << endl;
        }
    }

    return 0;
}

