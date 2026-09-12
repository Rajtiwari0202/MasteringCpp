#include <bits/stdc++.h>
using namespace std;

void selection_sort(int arr[], int n) {
    int total_passes = 0;

    // selection sort
    for (int i = 0; i < n - 1; i++) {
        int mini = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[mini]) {
                mini = j;
            }
        }
        swap(arr[mini], arr[i]);
        total_passes++;

        cout << "After pass " << total_passes << ": ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << "\n";
    }

    cout << "Total number of passes: " << total_passes << "\n";
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Before selection sort: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    selection_sort(arr, n);

    return 0;
}
