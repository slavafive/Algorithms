#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class SegmentTree {

    vector<long> a;
    vector<long> tree;
    int n;
    long NEUTRAL = INT32_MAX;

    void expand(vector<long> &a) {
        n = a.size();
        n = pow(2, ceil(log2(n)));
        this->a.resize(n, NEUTRAL);
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
        tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
    }

    long query(int l, int r, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            return tree[v];
        }
        if (rx < l || lx > r) {
            return NEUTRAL;
        }
        int m = (lx + rx) / 2;
        long left_result = query(l, r, lx, m, 2 * v + 1);
        long right_result = query(l, r, m + 1, rx, 2 * v + 2);
        return min(left_result, right_result);
    }

    void set(int i, long value, int lx, int rx, int v) {
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
        tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
    }

public:

    SegmentTree(vector<long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    long query(int l, int r) {
        return query(l, r, 0, n - 1, 0);
    }

    void set(int i, long value) {
        set(i, value, 0, n - 1, 0);
    }

    void print() {
        for (long value : tree) {
            cout << value << " ";
        }
        cout << endl;
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    vector<long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < m; i++) {
        int operation, first, second;
        cin >> operation >> first >> second;
        if (operation == 1) {
            tree.set(first, second);
        } else if (operation == 2) {
            cout << tree.query(first, second - 1) << endl;
        }
    }

    return 0;
}

