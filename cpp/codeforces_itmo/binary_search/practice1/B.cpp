#include <iostream>
#include <vector>

using namespace std;

int leftmost_binary_search(vector<int> &a, int x) {
    int l = -1;
    int r = a.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (a[m] <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        int number;
        cin >> number;
        int result = leftmost_binary_search(a, number);
        cout << result + 1 << endl;
    }

    return 0;
}

