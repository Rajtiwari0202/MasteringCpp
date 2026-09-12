#include<iostream>
using namespace std;

void swap(int &num1,int &num2){
    int temp = num1;
    num1=num2;
    num2=temp;

}
int main(){
    int x,y;
    cin >> x;
    cin >> y;
    swap(x,y);
    cout << x << " " << y;
    return 0;
}