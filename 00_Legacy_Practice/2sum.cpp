#include <iostream>
#include <unordered_map>
using namespace std;

pair<int, int> twoSum(int arr[], int n, int K) {
    unordered_map<int, int> mp; // value → index

    for (int i = 0; i < n; i++) {
        int complement = K - arr[i];

        if (mp.find(complement) != mp.end()) {
            return {mp[complement], i}; // found
        }

        mp[arr[i]] = i; // store value and index
    }

    return {-1, -1}; // not found
}

int main() {
    int arr[] = {2, 7, 11, 15};
    int K = 9;
    int n = sizeof(arr) / sizeof(arr[0]);

    pair<int, int> res = twoSum(arr, n, K);
    if (res.first != -1)
        cout << "Indices: (" << res.first << ", " << res.second << ")\n";
    else
        cout << "No such pair found.\n";

    return 0;
}
