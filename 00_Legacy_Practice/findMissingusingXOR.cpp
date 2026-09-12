#include <iostream>
using namespace std;

int findMissing(int arr[], int n) {
    int xor1 = 0, xor2 = 0;

    // XOR of all numbers from 1 to n+1
    for (int i = 1; i <= n + 1; i++)
        xor1 ^= i;

    // XOR of all array elements
    for (int i = 0; i < n; i++)
        xor2 ^= arr[i];

    // The missing number is:
    return xor1 ^ xor2;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Missing number is: " << findMissing(arr, n) << endl;
    return 0;
}
