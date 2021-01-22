#include <iostream>
#include <vector>

using namespace std;

class DSU {

public:

    vector<int> link, size, minimum, maximum;

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

    void unite(int a, int b) {
        if (same(a, b)) {
            return;
        }
        a = find(a);
        b = find(b);
        if (size[a] < size[b]) {
            swap(a, b);
        }
        size[a] += size[b];
        minimum[a] = min(minimum[a], minimum[b]);
        maximum[a] = max(maximum[a], maximum[b]);
        link[b] = a;
    }

    DSU(int n) {
        link.resize(n);
        size.resize(n);
        minimum.resize(n);
        maximum.resize(n);
        for (int i = 0; i < n; i++) {
            link[i] = minimum[i] = maximum[i] = i;
            size[i] = 1;
        }
    }

};

int main() {

    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    DSU dsu = DSU(n);
    for (int i = 0; i < m; i++) {
        string operation;
        int a, b;
        cin >> operation;
        if (operation == "union") {
            cin >> a >> b;
            dsu.unite(a - 1, b - 1);
        } else if (operation == "get") {
            cin >> a;
            b = dsu.find(a - 1);
            cout << dsu.minimum[b] + 1 << " " << dsu.maximum[b] + 1 << " " << dsu.size[b] << "\n";
        }
    }

    return 0;
}

