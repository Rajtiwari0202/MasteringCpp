#include<iostream>
#include<climits>
using namespace std;
int secondLargest(int arr[], int n) {
    int largest = INT_MIN;
    for (int i = 0; i < n; i++)
        largest = max(largest, arr[i]);

    int second = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] != largest) {
            second = max(second, arr[i]);
        }
    }

    return (second == INT_MIN) ? -1 : second;
}
int secondLargest2(int arr[], int n) {
    int largest = INT_MIN, second = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > largest) {
            second = largest;
            largest = arr[i];
        } else if (arr[i] > second && arr[i] != largest) {
            second = arr[i];
        }
    }

    return (second == INT_MIN) ? -1 : second;
}

int main(){
    int arr[]={4,6,7,12,11,17,12,7,6};
    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<secondLargest(arr,n);
}