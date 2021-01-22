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

};

int main() {

    int n, m, j = 0;
    cin >> n;
    vector<long long> first(ceil(n * 0.5)), second(floor(0.5 * n));
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            cin >> first[j];
        } else {
            cin >> second[j++];
        }
    }

    cin >> m;
    SegmentTree first_tree = SegmentTree(first);
    SegmentTree second_tree = SegmentTree(second);

    for (int i = 0; i < m; i++) {
        int operation, a, b;
        cin >> operation >> a >> b;
        if (operation == 0) {
            a -= 1;
            if (a % 2 == 0) {
                first_tree.set(a / 2, b);
            } else {
                second_tree.set(a / 2, b);
            }
        } else if (operation == 1) {
            a -= 1;
            b -= 1;
            long first_result, second_result;
            if (a % 2 == 0 && b % 2 == 0) {
                first_result = first_tree.sum(a / 2, b / 2);
                second_result = -second_tree.sum(a / 2, b / 2 - 1);
            } else if (a % 2 == 1 && b % 2 == 0) {
                first_result = -first_tree.sum(a / 2 + 1, b / 2);
                second_result = second_tree.sum(a / 2, b / 2 - 1);
            } else if (a % 2 == 0 && b % 2 == 1) {
                first_result = first_tree.sum(a / 2, b / 2);
                second_result = -second_tree.sum(a / 2, b / 2 + 1);
            } else {
                first_result = -first_tree.sum(a / 2 + 1, b / 2 + 1);
                second_result = second_tree.sum(a / 2, b / 2 + 1);
            }
            cout << first_result + second_result << "\n";
        }
    }

    return 0;
}
