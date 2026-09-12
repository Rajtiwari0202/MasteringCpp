#include <iostream>
using namespace std;

void leftRotateByOne(int arr[], int n) {
    if (n == 0) return;

    int temp = arr[0]; // Store the first element

    // Shift elements to the left
    for (int i = 1; i < n; i++) {
        arr[i - 1] = arr[i];
    }

    arr[n - 1] = temp; // Place the first element at the end
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    leftRotateByOne(arr, n);

    cout << "Array after left rotation by one: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
