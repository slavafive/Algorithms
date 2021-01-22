#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Matrix {
    int a, b, c, d;
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};

class SegmentTree {

    int n, r;
    vector<Matrix> a;
    vector<Matrix> tree;
    const Matrix NEUTRAL = Matrix(1, 0, 0, 1);

    void update(int v) {
        tree[v] = multiply(tree[2 * v + 1], tree[2 * v + 2]);
    }

    Matrix multiply(Matrix &first, Matrix &second) {
        return Matrix((first.a * second.a + first.b * second.c) % r, (first.a * second.b + first.b * second.d) % r,
                      (first.c * second.a + first.d * second.c) % r,(first.c * second.b + first.d * second.d) % r);
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

    Matrix product(int l, int r, int lx, int rx, int v) {
        if (l <= lx && rx <= r) {
            return tree[v];
        }
        if (rx < l || r < lx) {
            return NEUTRAL;
        }
        int m = (lx + rx) / 2;
        Matrix left = product(l, r, lx, m, 2 * v + 1);
        Matrix right = product(l, r, m + 1, rx, 2 * v + 2);
        return multiply(left, right);
    }

public:

    SegmentTree(vector<Matrix> &a, int r) {
        this->r = r;
        n = pow(2, ceil(log2(a.size())));
        this->a.resize(n);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        tree.resize(2 * n - 1, NEUTRAL);
        build(0, n - 1, 0);
    }

    Matrix product(int l, int r) {
        return product(l, r, 0, n - 1, 0);
    }

};

int main() {

    ios_base::sync_with_stdio(false);

    int r, n, m;
    cin >> r >> n >> m;
    vector<Matrix> matrices(n);
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        matrices[i] = Matrix(a, b, c, d);
    }
    SegmentTree tree = SegmentTree(matrices, r);
    for (int i = 0; i < m; i++) {
        int left, right;
        cin >> left >> right;
        Matrix result = tree.product(left - 1, right - 1);
        cout << result.a << " " << result.b << "\n" << result.c << " " << result.d << "\n\n";
    }

    return 0;
}

