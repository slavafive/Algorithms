#include <iostream>
#include <vector>

using namespace std;

class DSU {

public:

    int n;
    vector<int> link, size, experience;

    DSU(int n) {
        this->n = n;
        link.resize(n);
        size.resize(n);
        experience.resize(n);
        for (int i = 0; i < n; i++) {
            link[i] = i;
            size[i] = 1;
            experience[i] = 0;
        }
    }

    int find(int x) {
        if (x == link[x]) {
            return x;
        }
        return link[x] = find(link[x]);
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
        link[b] = a;
    }

    void add(int a, int value) {
        a = find(a);
        experience[a] += value;
    }

    int get(int a) {
        return experience[a];
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    DSU dsu = DSU(n);
    for (int i = 0; i < m; i++) {
        int x, v;
        string operation;
        cin >> operation;
        if (operation == "join") {
            cin >> x >> v;
            dsu.unite(x - 1, v - 1);
        } else if (operation == "get") {
            cin >> x;
            cout << dsu.get(x - 1) << "\n";
        } else if (operation == "add") {
            cin >> x >> v;
            dsu.add(x - 1, v);
        }
    }

    return 0;
}
