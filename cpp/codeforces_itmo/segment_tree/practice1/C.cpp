#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class SegmentTree {

    vector<long> a;
    vector<pair<long, int>> tree;
    int n;
    long NEUTRAL = INT32_MAX;

    void expand(vector<long> &a) {
        n = a.size();
        n = pow(2, ceil(log2(n)));
        this->a.resize(n, NEUTRAL);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, make_pair(NEUTRAL, 1));
    }

    void merge(int v) {
        tree[v].first = min(tree[2 * v + 1].first, tree[2 * v + 2].first);
        tree[v].second = count(tree[2 * v + 1], tree[2 * v + 2]);
    }

    int count(pair<long, int> left, pair<long, int> right) {
        if (left.first == right.first) {
            return left.second + right.second;
        } else {
            return left.first < right.first ? left.second : right.second;
        }
    }

    void build(int lx, int rx, int v) {
        if (lx == rx) {
            tree[v] = make_pair(a[lx], 1);
            return;
        }
        int m = (lx + rx) / 2;
        build(lx, m, 2 * v + 1);
        build(m + 1, rx, 2 * v + 2);
        merge(v);
    }

    pair<long, int> query(int l, int r, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            return tree[v];
        }
        if (rx < l || lx > r) {
            return make_pair(NEUTRAL, 0);
        }
        int m = (lx + rx) / 2;
        pair<long, int> left_result = query(l, r, lx, m, 2 * v + 1);
        pair<long, int> right_result = query(l, r, m + 1, rx, 2 * v + 2);
        return make_pair(min(left_result.first, right_result.first), count(left_result, right_result));
    }

    void set(int i, long value, int lx, int rx, int v) {
        if (lx == rx && lx == i) {
            tree[v] = make_pair(value, 1);
            return;
        }
        if (i < lx || rx < i) {
            return;
        }
        int m = (lx + rx) / 2;
        set(i, value, lx, m, 2 * v + 1);
        set(i, value, m + 1, rx, 2 * v + 2);
        merge(v);
    }

public:

    SegmentTree(vector<long> &a) {
        expand(a);
        build(0, n - 1, 0);
    }

    pair<long, int> query(int l, int r) {
        return query(l, r, 0, n - 1, 0);
    }

    void set(int i, long value) {
        set(i, value, 0, n - 1, 0);
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
            pair<long, int> element = tree.query(first, second - 1);
            cout << element.first << " " << element.second << endl;
        }
    }

    return 0;
}


