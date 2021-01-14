#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<pair<int, int>, int>> counting_sort(vector<pair<pair<int, int>, int>> &a) {
    int n = a.size();
    int max_element = a[0].first.second;
    for (int i = 0; i < n; i++) {
        if (max_element < a[i].first.second) {
            max_element = a[i].first.second;
        }
    }
    vector<int> b(max_element + 1);
    vector<pair<pair<int, int>, int>> c(a.size());

    for (int i = 0; i < n; i++) b[a[i].first.second] += 1;
    for (int i = 1; i < b.size(); i++) b[i] += b[i - 1];
    for (int i = n - 1; i >= 0; i--) c[--b[a[i].first.second]] = a[i];

    for (int i = 0; i < n; i++) a[i] = c[i];
    for (int i = 0; i < b.size(); i++) b[i] = 0;

    max_element = a[0].first.first;
    for (int i = 0; i < n; i++) if (max_element < a[i].first.first) max_element = a[i].first.first;

    for (int i = 0; i < n; i++) b[a[i].first.first] += 1;
    for (int i = 1; i < b.size(); i++) b[i] += b[i - 1];
    for (int i = n - 1; i >= 0; i--) c[--b[a[i].first.first]] = a[i];

    return c;
}

vector<int> build_suffix_array(string s) {
    s += "$";
    int n = s.size();
    vector<int> p(n), c(n);

    {
        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1 << k) < n) {
        // k -> k + 1
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
//        sort(a.begin(), a.end());
        a = counting_sort(a);
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        k++;
    }

    return p;
}

int main() {
    string s;
    cin >> s;
    vector<int> p = build_suffix_array(s);
//    for (int i = 0; i < p.size(); i++) {
//        cout << p[i] << " " << s.substr(p[i], s.size() - p[i]) << endl;
//    }
    for (int i = 0; i < p.size(); i++) {
        cout << p[i] << " ";
    }

    return 0;
}


