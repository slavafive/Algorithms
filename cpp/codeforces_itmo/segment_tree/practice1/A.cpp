#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class SegmentTree {

    vector<long long> a;
    vector<long long> tree;
    int n;

    void expand(vector<long long> &a) {
        n = a.size();
        n = pow(2, ceil(log2(n)));
        this->a.resize(n, 0);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, 0);
    }

    void build(int l, int r, int v) {
        if (l == r) {
            tree[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1);
        build(m + 1, r, 2 * v + 2);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    long long sum(int l, int r, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            return tree[v];
        }
        if (l > rx || r < lx) {
            return 0;
        }
        int m = (lx + rx) / 2;
        long long left_result = sum(l, r, lx, m, 2 * v + 1);
        long long right_result = sum(l, r, m + 1, rx, 2 * v + 2);
        return left_result + right_result;
    }

    void set(int i, int value, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            tree[v] = value;
            return;
        }
        if (i < lx || i > rx) {
            return;
        }
        int m = (lx + rx) / 2;
        set(i, value, lx, m, 2 * v + 1);
        set(i, value, m + 1, rx, 2 * v + 2);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

public:

    SegmentTree(vector<long long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, n - 1, 0);
    }

    void set(int i, int value) {
        set(i, value, 0, n - 1, 0);
    }

    void print() {
        for (long long value : tree) {
            cout << value << " ";
        }
        cout << endl;
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
        int operation, first, second;
        cin >> operation >> first >> second;
        if (operation == 1) {
            tree.set(first, second);
        } else if (operation == 2) {
            cout << tree.sum(first, second - 1) << endl;
        }
    }

    return 0;
}
