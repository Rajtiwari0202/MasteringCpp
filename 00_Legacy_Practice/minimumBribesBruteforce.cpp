#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> q(n);
    for(int i=0;i<n;i++){
        cin>>q[i];
    }
for(int i=0;i<n;i++){
        if(q[i]-(i+1)>2){
            cout<<"Too chaotic"<<endl;
            return 0;
        }
    }
    int bribes=0;
    for(int i=0;i<n;i++){
        for(int j=max(0,q[i]-2);j<i;j++){
            if(q[j]>q[i]){
                bribes++;
            }
        }
    }
    cout<<bribes<<endl;
}
