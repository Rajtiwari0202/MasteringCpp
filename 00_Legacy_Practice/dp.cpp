#include <bits/stdc++.h>
using namespace std;
int f(int n,vector<int> dp(n + 1, -1))
{
    if(n<=1) return n;
    if(dp[n] != -1) return dp[n];
    return dp[n]=f(n-1)+f(n-2);
}
 int main(){
    
    int n;
    cin >> n;
    vector<int> dp(n,-1);
    cout << f(n,dp);
    return 0;
 }