#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {

    int n, NEUTRAL = 0;
    vector<long long> a, tree, add;

    void update(int v) {
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
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

    void push(int v) {
        if (2 * v + 2 < tree.size()) {
            add[2 * v + 1] += add[v];
            add[2 * v + 2] += add[v];
            add[v] = 0;
        } else {
            tree[v] += add[v];
        }
    }

    void add_to_segment(int l, int r, int value, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            push(v);
            add[v] = value;
            return;
        }
        if (rx < l || r < lx) {
            return;
        }
        int m = (lx + rx) / 2;
        add_to_segment(l, r, value, lx, m, 2 * v + 1);
        add_to_segment(l, r, value, m + 1, rx, 2 * v + 2);
    }

    long long get_value(int i, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            return tree[v] + add[v];
        }
        if (i < lx || rx < i) {
            return NEUTRAL;
        }
        push(v);
        int m = (lx + rx) / 2;
        long long left_res = get_value(i, lx, m, 2 * v + 1);
        long long right_res = get_value(i, m + 1, rx, 2 * v + 2);
        return left_res + right_res;

    }

public:

    SegmentTree(vector<long long> &a) {
        n = pow(2, ceil(log2(a.size())));
        this->a.resize(n, NEUTRAL);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, NEUTRAL);
        add.resize( 2 * n - 1, NEUTRAL);
        build(0, n - 1, 0);
    }

    void add_to_segment(int l, int r, int value) {
        add_to_segment(l, r, value, 0, n - 1, 0);
    }

    long long get_value(int i) {
        return get_value(i, 0, n - 1, 0);
    }


};

int main() {

    int n, queries;
    cin >> n >> queries;
    vector<long long> a(n, 0);
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < queries; i++) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            int l, r, value;
            cin >> l >> r >> value;
            tree.add_to_segment(l, r - 1, value);
        } else if (operation == 2) {
            int j;
            cin >> j;
            cout << tree.get_value(j) << endl;
        }
    }

    return 0;
}

