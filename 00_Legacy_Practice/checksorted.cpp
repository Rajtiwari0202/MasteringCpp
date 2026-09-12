#include <iostream>
using namespace std;

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false; // found unsorted pair
        }
    }
    return true; // entire array is sorted
}

int main() {
    int arr[] = {1, 2, 2, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, n))
        cout << "Array is sorted." << endl;
    else
        cout << "Array is NOT sorted." << endl;

    return 0;
}
