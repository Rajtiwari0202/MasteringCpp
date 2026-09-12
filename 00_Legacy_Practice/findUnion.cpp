#include <iostream>
#include <set>
using namespace std;

void printUnion(int arr1[], int arr2[], int n, int m) {
    set<int> s;

    // Insert all elements into the set
    for (int i = 0; i < n; i++)
        s.insert(arr1[i]);

    for (int i = 0; i < m; i++)
        s.insert(arr2[i]);

    // Print the result
    cout << "Union: ";
    for (auto it : s)
        cout << it << " ";
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
