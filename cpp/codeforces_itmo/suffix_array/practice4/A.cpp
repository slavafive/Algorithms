#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> build_suffix_array(string s) {
    s += "$";
    int n = s.size();
    vector<int> c(n), p(n);

    {
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
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
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
        k++;
    }

    return p;
}

vector<int> build_lcp(string s, vector<int> p) {
    int k = 0;
    int n = s.size() + 1;
    vector<int> c(n), lcp(n);
    for (int i = 0; i < n; i++) c[p[i]] = i;
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];
        int j = p[pi - 1];
        while (s[p[pi] + k] == s[j + k]) k++;
        lcp[pi] = k;
        k = max(k - 1, 0);
    }
    return lcp;
}

int main() {

    string s;
    cin >> s;
    vector<int> p = build_suffix_array(s);
    vector<int> lcp = build_lcp(s, p);
    for (int i = 0; i < p.size(); i++) cout << p[i] << " ";
    cout << endl;
    for (int i = 1; i < lcp.size(); i++) cout << lcp[i] << " ";

    return 0;
}

