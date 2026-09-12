#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i; // Return the index
    }
    return -1; // Not found
}

int main() {
    int arr[] = {5, 3, 7, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 1;

    int result = linearSearch(arr, n, x);

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
