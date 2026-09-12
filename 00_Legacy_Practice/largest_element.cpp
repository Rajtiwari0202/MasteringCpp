#include <iostream>
#include <climits> // for INT_MIN
using namespace std;

int findLargest(int arr[], int n) {
    int maxVal = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

int main() {
    int arr[] = {3, 17, 9, 4, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Largest Element: " << findLargest(arr, n) << endl;
    return 0;
}
