#include <iostream>
#include <vector>

using namespace std;

int get_max_element(vector<int> &a) {
    int res = a[0];
    for (int i = 1; i < a.size(); i++) {
        res = res > a[i] ? res : a[i];
    }
    return res;
}

vector<int> counting_sort(vector<int> &a) {
    int n = a.size();
    int max = get_max_element(a);
    vector<int> b(max + 1);
    for (int i = 0; i < n; i++) {
        b[a[i]]++;
    }
    for (int i = 2; i < b.size(); i++) {
        b[i] += b[i - 1];
    }
    vector<int> c(n);
    for (int i = n - 1; i >= 0; i--) {
        int index = b[a[i]]-- - 1;
        c[index] = a[i];
    }
    return c;
}

int main() {

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> c = counting_sort(v);
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }

    return 0;

}