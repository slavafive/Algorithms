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

int rightmost_binary_search(vector<int> &a, int x) {
    int l = -1;
    int r = a.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (a[m] < x) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

void merge(vector<int> &a, int left1, int right1, int left2, int right2) {
    int i = left1;
    int j = left2;
    int k = 0;
    vector<int> b(right2 - left1 + 1);
    while (i <= right1 && j <= right2) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    while (i <= right1) {
        b[k++] = a[i++];
    }
    while (j <= right2) {
        b[k++] = a[j++];
    }
    for (int t = 0; t < b.size(); t++) {
        a[left1 + t] = b[t];
    }
}

void mergesort(vector<int> &a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, m + 1, r);
    }
}

int main() {

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    mergesort(a, 0, n - 1);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int first, second;
        cin >> first >> second;
        int left_index = rightmost_binary_search(a, first);
        int right_index = leftmost_binary_search(a, second);
        cout << right_index - left_index + 1 << " ";
    }

}
