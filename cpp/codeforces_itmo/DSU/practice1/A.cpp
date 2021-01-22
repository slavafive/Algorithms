#include <iostream>
#include <vector>

using namespace std;

class DSU {

    vector<int> link, size;
    int n;

public:

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (size[a] < size[b]) {
            swap(a, b);
        }
        size[a] += size[b];
        link[b] = a;
    }

    int find(int x) {
        if (x == link[x]) {
            return x;
        }
        link[x] = find(link[x]);
        return link[x];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    DSU(int n) {
        this->n = n;
        link.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            link[i] = i;
            size[i] = 1;
        }
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    DSU dsu = DSU(n);
    for (int i = 0; i < m; i++) {
        string operation;
        int u, v;
        cin >> operation >> u >> v;
        u -= 1;
        v -= 1;
        if (operation == "union") {
            dsu.unite(u, v);
        } else if (operation == "get") {
            cout << (dsu.same(u, v) ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}