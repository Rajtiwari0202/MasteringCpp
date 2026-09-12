#include <iostream>
using namespace std;

void printUnion(int arr1[], int arr2[], int n, int m) {
    int i = 0, j = 0;

    cout << "Union: ";
    while (i < n && j < m) {
        // Avoid duplicates in arr1
        if (i > 0 && arr1[i] == arr1[i - 1]) {
            i++;
            continue;
        }
        // Avoid duplicates in arr2
        if (j > 0 && arr2[j] == arr2[j - 1]) {
            j++;
            continue;
        }

        if (arr1[i] < arr2[j])
            cout << arr1[i++] << " ";
        else if (arr2[j] < arr1[i])
            cout << arr2[j++] << " ";
        else { // Both are same
            cout << arr1[i++] << " ";
            j++;
        }
    }

    // Remaining elements of arr1
    while (i < n) {
        if (i == 0 || arr1[i] != arr1[i - 1])
            cout << arr1[i] << " ";
        i++;
    }

    // Remaining elements of arr2
    while (j < m) {
        if (j == 0 || arr2[j] != arr2[j - 1])
            cout << arr2[j] << " ";
        j++;
    }

    cout << endl;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);

    printUnion(arr1, arr2, n, m);

    return 0;
}
