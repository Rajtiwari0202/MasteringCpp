#include <iostream>
using namespace std;

int findMaxConsecutiveOnes(int arr[], int n) {
    int count = 0, maxCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            count++;
            maxCount = max(maxCount, count);
        } else {
            count = 0;
        }
    }

    return maxCount;
}

int main() {
    int arr[] = {1, 1, 0, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Maximum Consecutive 1s: " << findMaxConsecutiveOnes(arr, n) << endl;
    return 0;
}
