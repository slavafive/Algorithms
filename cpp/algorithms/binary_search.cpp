#include <iostream>
#include <vector>

using namespace std;

int left_binary_search(vector<int> &a, int key) {
    int left = -1;
    int right = a.size();
    while (left + 1 < right) {
        int middle = (left + right) / 2;
        if (a[middle] < key) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int right_binary_search(vector<int> &a, int key) {
    int left = -1;
    int right = a.size();
    while (left + 1 < right) {
        int middle = (left + right) / 2;
        if (a[middle] <= key) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right - 1;
}

int main() {

    vector<int> a = {2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 7, 7, 8, 8};
    int left = left_binary_search(a, 2);
    int right = right_binary_search(a, 2);
    cout << left << " - " << right;

    return 0;
}

