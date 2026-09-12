#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> removeDuplicatesUnsorted(int arr[], int n) {
    unordered_set<int> seen;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (seen.find(arr[i]) == seen.end()) {
            seen.insert(arr[i]);
            result.push_back(arr[i]);
        }
    }

    return result;
}

int main() {
    int arr[] = {4, 2, 2, 4, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    vector<int> res = removeDuplicatesUnsorted(arr, n);
    cout << "Unique elements: ";
    for (int val : res) cout << val << " ";
    cout << endl;

    return 0;
}
