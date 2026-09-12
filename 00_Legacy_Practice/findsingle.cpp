#include <iostream>
using namespace std;

int findSingle(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];  // XOR all elements
    }
    return result;
}

int main() {
    int arr[] = {2, 3, 5, 4, 5, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Element that appears once: " << findSingle(arr, n) << endl;
    return 0;
}
