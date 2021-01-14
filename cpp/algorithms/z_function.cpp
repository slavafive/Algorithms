#include <iostream>
#include <vector>

using namespace std;

vector<int> z_function(string s) {
    vector<int> z(s.size());
    int n = s.size();
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        };
    }
    z[0] = 0;
    return z;
}

int main() {

    string s;
    cin >> s;
    vector<int> z = z_function(s);
    for (int i = 0; i < z.size(); i++) {
        cout << z[i] << " ";
    }

    return 0;
}

