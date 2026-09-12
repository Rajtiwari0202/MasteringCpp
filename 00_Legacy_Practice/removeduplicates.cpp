#include <iostream>
using namespace std;

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int i = 0; // pointer for position of last unique
    for (int j = 1; j < n; j++) {
        if (arr[j] != arr[i]) {
            i++;            // move i to next position
            arr[i] = arr[j]; // copy unique element
        }
    }

    return i + 1; // number of unique elements
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int newLength = removeDuplicates(arr, n);
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < newLength; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
