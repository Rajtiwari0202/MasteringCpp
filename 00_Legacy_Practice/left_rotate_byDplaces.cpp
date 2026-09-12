#include <iostream>
using namespace std;

void leftRotate(int arr[], int n, int d) {
    d = d % n; // Handle if d > n

    int temp[d];
    for (int i = 0; i < d; i++)
        temp[i] = arr[i]; // Store first d elements

    for (int i = d; i < n; i++)
        arr[i - d] = arr[i]; // Shift remaining elements

    for (int i = 0; i < d; i++)
        arr[n - d + i] = temp[i]; // Copy back temp
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int d = 2;

    leftRotate(arr, n, d);

    cout << "Array after " << d << " left rotations: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
