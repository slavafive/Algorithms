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
        this->a.resize(n, NEUTRAL);
        for (int i = 0; i < n; i++) {
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
        if (i < lx || rx < i) {
            return;
        }
        int m = (lx + rx) / 2;
        invert(i, lx, m, 2 * v + 1);
        invert(i, m + 1, rx, 2 * v + 2);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    int find_kth_one(int k, int lx, int rx, int v) {
        if (lx == rx) {
            return lx;
        }
        int m = (lx + rx) / 2;
        if (k < tree[2 * v + 1]) {
            return find_kth_one(k, lx, m, 2 * v + 1);
        } else {
            return find_kth_one(k - tree[2 * v + 1], m + 1, rx, 2 * v + 2);
        }
    }

public:

    SegmentTree(vector<int> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    void invert(int i) {
        invert(i, 0, n - 1, 0);
    }

    int find_kth_one(int k) {
        return find_kth_one(k, 0, n - 1, 0);
    }

};

int main() {

    int n;
    cin >> n;
    vector<int> inv(n), p(n);
    vector<int> a(n, 1);
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < n; i++) {
        cin >> inv[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        int kth_one = tree.find_kth_one(inv[i]);
        p[i] = n - kth_one;
        tree.invert(kth_one);
    }
    for (int i = 0; i < n; i++) {
        cout << p[i] << " ";
    }

    return 0;
}