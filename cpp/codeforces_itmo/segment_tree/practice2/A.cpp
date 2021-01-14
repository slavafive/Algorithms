#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Node {

    long sum;
    long seg;
    long pref;
    long suf;

    Node() {
        set_value(0);
    }

    void set_value(long value) {
        sum = seg = pref = suf = value;
    }

};

class SegmentTree {

    vector<long long> a;
    vector<Node> tree;
    int n;

    void expand(vector<long long> &a) {
        n = a.size();
        n = pow(2, ceil(log2(n)));
        this->a.resize(n, 0);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, Node());
    }

    void merge(Node &center, Node &left, Node &right) {
        center.sum = left.sum + right.sum;
        center.seg = max(left.suf + right.pref, max(left.seg, right.seg));
        center.pref = max(left.pref, left.sum + right.pref);
        center.suf = max(left.suf + right.sum, right.pref);
    }

    void build(int lx, int rx, int v) {
        if (lx == rx) {
            tree[v].set_value(a[lx]);
            return;
        }
        int m = (lx + rx) / 2;
        build(lx, m, 2 * v + 1);
        build(m + 1, rx, 2 * v + 2);
        merge(tree[v], tree[2 * v + 1], tree[2 * v + 2]);
    }

    void set(int i, long value, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            tree[v].set_value(value);
            return;
        }
        if (i < lx || i > rx) {
            return;
        }
        int m = (lx + rx) / 2;
        set(i, value, lx, m, 2 * v + 1);
        set(i, value, m + 1, rx, 2 * v + 2);
        merge(tree[v], tree[2 * v + 1], tree[2 * v + 2]);
    }

    long get_maximum_sum(int lx, int rx, int v) {
        return tree[v].seg > 0 ? tree[v].seg : 0;
    }

public:

    SegmentTree(vector<long long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    void set(int i, int value) {
        set(i, value, 0, n - 1, 0);
    }

    long get_maximum_sum() {
        return get_maximum_sum(0, n - 1, 0);
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
    cout << tree.get_maximum_sum() << endl;
    for (int i = 0; i < m; i++) {
        int j, value;
        cin >> j >> value;
        tree.set(j, value);
        cout << tree.get_maximum_sum() << endl;
    }

    return 0;
}

