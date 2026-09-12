#include <iostream>
using namespace std;

void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

void leftRotate(int arr[], int n, int d) {
    d = d % n; // To handle cases when d > n

    reverse(arr, 0, d - 1);       // Step 1
    reverse(arr, d, n - 1);       // Step 2
    reverse(arr, 0, n - 1);       // Step 3
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
