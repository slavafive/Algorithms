#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {

    vector<int> a;
    vector<int> tree;
    int n;
    const int NEUTRAL = 0;

    void expand(vector<int> &a) {
        n = pow(2, ceil(log2(a.size())));
        this->a.resize(n,NEUTRAL);
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

    int sum(int l, int r, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            return tree[v];
        }
        if (rx < l || r < lx) {
            return NEUTRAL;
        }
        int m = (lx + rx) / 2;
        return sum(l, r, lx, m, 2 * v + 1) + sum(l, r, m + 1, rx, 2 * v + 2);
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
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

public:

    int sum(int l, int r) {
        return sum(l, r, 0, n - 1, 0);
    }

    void set(int i, int value) {
        set(i, value, 0, n - 1, 0);
    }

    SegmentTree(vector<int> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

};

int main() {

    int n;
    cin >> n;
    vector<int> p(n), a(n + 1, 0), new_p(n);
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        new_p[i] = tree.sum(p[i], n);
        tree.set(p[i], 1);
    }
    for (int i = 0; i < n; i++) {
        cout << new_p[i] << " ";
    }

}