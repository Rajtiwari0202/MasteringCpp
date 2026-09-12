#include <iostream>
#include <vector>
using namespace std;

void sort(int* arr, int s, int e, int ord) {
    for (int i = s; i <= e; i++) {
        for (int j = i + 1; j <= e; j++) {
            if ((ord == 0 && arr[i] > arr[j]) || (ord == 1 && arr[i] < arr[j])) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

int main() 
{
    vector<int> arr = {4, 3, 1, 7, 8, 9, 6, 5, 0, 2};
    int n = arr.size();
    int k = 6;
    sort(arr.data(), 0, k - 1, 0);
    sort(arr.data(), k, n - 1, 1);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
