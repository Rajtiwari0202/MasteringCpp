#include <iostream>
#include <vector> //#include <bits/c++.h>
using namespace std;
//BRUTE FORCE APPROACH
int main() {
    int n = 5;
    int arr[5] = {1, 2, 3, 4, 5};

    int maxSum = +2147483648;

    for(int st=0; st<n; st++) {
        int currSum = 0;
        for(int end=st; end<n; end++) {
            currSum += arr[end];
            maxSum = max(currSum, maxSum);
        }
        cout << "max subarray sum = " << maxSum << endl;
    }
    return 0;
}
//Kadane's algorithm
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int currSum = 0, maxSum = INT_MIN;

        for(int val : nums) {
            currSum += val;
            maxSum = max(currSum, maxSum);
            
            if(currSum < 0) {
                currSum = 0;
            }
        }
        return maxSum;
    }
    
};
