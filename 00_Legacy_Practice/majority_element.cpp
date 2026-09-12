#include<bits/stdc++.h>
using namespace std;

//boyer moore's voting algorithm
int majority_element(int arr[],int n){
    int cnt=0;
    int el;
    for(int i=0;i<n;i++){
        if(cnt==0){
            cnt=1;
            el = arr[i];
        }
        else if(arr[i] == el){
            cnt++;
        }
        else{
            cnt--;
        }
        
    }int cnt1=0;
    for(int i=0;i<n;i++){
        if(arr[i]==el){
            cnt ++;
        }
        if(cnt > (n/2))
            return el;
    }
    return -1;
}

int majority_element_by_sorting(int arr[], int n){
    sort(arr,arr+n);
    for (int i=0;i<n;i++){
        if(arr[i] == arr[n/2])
            return arr[n/2];
    }
}
int majority_element_by_hashing(int arr[], int n){
    map<int,int>mpp;
    for(int i=0;i<n;i++){
        mpp[arr[i]]++;
    }
    for(auto it:mpp){
        if(it.second > (n/2)){
            return it.first;
        }
    }
    return -1;
}
int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    cout << majority_element(arr,n);
    cout << endl;
    cout << majority_element_by_sorting(arr,n);
    cout << endl;
    cout << majority_element_by_hashing(arr,n);
}