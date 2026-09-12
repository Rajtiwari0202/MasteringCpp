#include <iostream>
#include <unordered_map>
using namespace std;

int findSingle(int arr[], int n) {
    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++)
        freq[arr[i]]++;

    for (auto x : freq) {
        if (x.second == 1)
            return x.first;
    }

    return -1; // not found (should not happen)
}

int main() {
    int arr[] = {2, 3, 5, 4, 5, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Element that appears once: " << findSingle(arr, n) << endl;
    return 0;
}
