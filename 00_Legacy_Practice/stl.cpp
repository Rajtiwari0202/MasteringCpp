#include<bits/stdc++.h>//this contains all no need to add math and string separately
// #include<math.h>//for maths functions
// #include<string.h>//for string diff fucntionalities
using namespace std;
void print(){
    cout<<"Raj";
}
int sum(int a,int b){
    return a+b;
}
int main(){
    int a,b;
    cin>>a;
    cin>>b;
    int s=sum(a,b);
    cout<<s;
    for(int i=0;i<s;i++){
        print();
    }
    return 0;
}