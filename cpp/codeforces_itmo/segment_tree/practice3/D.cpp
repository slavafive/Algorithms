#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {

    vector<int> a;
    vector<int> tree;
    int n;
    int NEUTRAL = 0;

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
        if (rx < i || lx > i) {
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
        this->a.resize(n);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, NEUTRAL);
        build(0, n - 1, 0);
    }

    void set(int i, int value) {
        set(i, value, 0, n - 1, 0);
    }

    int sum(int l, int r) {
        return sum(l, r, 0, n - 1, 0);
    }

};

int main() {

    int n;
    cin >> n;
    vector<int> numbers(2 * n, 0), a(2 * n, 0), indices(n + 1, 0), answers(n + 1, 0);
    vector<bool> visited(n + 1, false);
    SegmentTree tree = SegmentTree(a);
    for (int i = 0; i < 2 * n; i++) {
        cin >> numbers[i];
    }
    for (int i = 0; i < 2 * n; i++) {
        if (visited[numbers[i]]) {
            tree.set(indices[numbers[i]], 0);
            answers[numbers[i]] += tree.sum(indices[numbers[i]], i - 1);
        } else {
            indices[numbers[i]] = i;
            tree.set(i, 1);
        }
        visited[numbers[i]] = !visited[numbers[i]];
    }

    a.resize(2 * n, 0);
    tree = SegmentTree(a);

    for (int i = 2 * n - 1; i >= 0; i--) {
        if (visited[numbers[i]]) {
            tree.set(indices[numbers[i]], 0);
            answers[numbers[i]] += tree.sum(i - 1, indices[numbers[i]]);
        } else {
            indices[numbers[i]] = i;
            tree.set(i, 1);
        }
        visited[numbers[i]] = !visited[numbers[i]];
    }

    for (int i = 1; i < answers.size(); i++) {
        cout << answers[i] << " ";
    }

    return 0;
}
