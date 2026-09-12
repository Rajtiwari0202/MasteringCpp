#include<iostream>
using namespace std;

void reverse(int arr[],int s,int e){
    while(s<e)
    {
        int temp=arr[s];
        arr[s]=arr[e];
        arr[e]=temp;
        s++;
        e--;
    }
}
void rotate(int arr[], int n,int k){
    k=k%n;
    reverse(arr,0,n-1);
    reverse(arr,0,k-1);
    reverse(arr,k,n-1);

}
int main(){
    int n=7;
    int k=4;
    int arr[]={4,3,1,7,8,6,9};
    rotate(arr,n,k);
    for(int i=0;i<n;i++)
    {
        cout << arr[i] << " ";
    }
}