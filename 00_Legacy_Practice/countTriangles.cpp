#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countTriangles1(vector<int>& arr) {
    int res = 0;
    for (int i = 0; i < arr.size(); i++)
        for (int j = i + 1; j < arr.size(); j++)
            for (int k = j + 1; k < arr.size(); k++) {
                if (arr[i] + arr[j] > arr[k] &&
                    arr[i] + arr[k] > arr[j] &&
                    arr[j] + arr[k] > arr[i]) {
                    res++;
                }
            }
    return res;
}
int countTriangles2(vector<int>& arr) {
    int n = arr.size();
    int res = 0;

    sort(arr.begin(), arr.end()); 
    for (int k = n - 1; k >= 2; k--) {
        int i = 0, j = k - 1;
        while (i < j) {
            if (arr[i] + arr[j] > arr[k]) {
                res += (j - i);
                j--;
            } else {
                i++;
            }
        }
    }
    return res;
}

int countTriangles3(vector<int>& arr) {
    int n = arr.size();
    int res = 0;

    sort(arr.begin(), arr.end());  // Sort array first

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = arr[i] + arr[j];
            // Find first index where arr[k] >= sum using lower_bound
            int k = lower_bound(arr.begin() + j + 1, arr.end(), sum) - arr.begin();
            int cnt = k - j - 1;
            res += cnt;
        }
    }

    return res;
}
int main() {
    vector<int> arr = {4,6,3,7};
    cout << countTriangles3(arr) << endl;
    return 0;
}
