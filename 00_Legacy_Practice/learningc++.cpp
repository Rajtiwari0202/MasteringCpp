#include <iostream>
#include <vector> //<bits/c++.h>
using namespace std;


// int main()
// {
//     int n = 11;
//     bool isPrime = true;

//     for(int i=2; i*i <= n; i++) {
//         if(n % i == 0) {//non prime
//             isPrime = false;
//             break;
//         }
//     }

//     if(isPrime == true) {
//         cout << "prime no.\n";
//     } else {
//         cout << "non prime no.\n";
//     }
//     return 0;
// }

//nested loops

// int main() {
//     int n = 6;

//     for(int i=0; i<n; i++) {//outer
//         char ch = 'A';
//         for(int j=1; j<=n; j++) {//inner => line start
//         cout << ch;
//         ch +=1; //65+1 => 66
//         } 
//         cout << endl;
//     }
    
//     return 0;
// }
// int main() {
//     int n = 3;

//     int num =1;

//     for(int i=0; i<n; i++) {
//         for(int j=0; j<n; j++) {
//             cout << num << " ";
//             num++;
//         }
//         cout << endl;
//     }

//     return 0;
// }
// int main() {
//     int n = 3;
//     char ch = 'A';
//     for(int i=0; i<n; i++) {//outer
        
//         for(int j=1; j<=n; j++) {//inner => line start
//         cout << ch;
//         ch +=1; //65+1 => 66
//         } 
//         cout << endl;
//     }
//     return 0;
// }
// int main() {
//     int n = 4;
//      for(int i=0; i<n; i++) {
//         for(int j=0; j<i+1; j++) {//i+1
//         cout << "*";
//         }
//         cout << endl;
//      }
//     return 0;
// }
// int main() {
//     int n = 4;

//     for(int i=0; i<n; i++) {
//         for(int j=0; j<i+1; j++) {
//             cout << (i+1) << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }
//floyd's triangle pattern
// int main() {
//     int n = 4;

//     int num = 1;
//     for(int i=0; i<n; i++) {
//         for(int j=i+1; j>0; j--){
//             cout << num << " ";
//             num++;
//         }
//         cout << endl;
        
//     }
//     return 0;
// }
// int main() {
//     int n = 4;

//     int num = 1;

//     for(int i=0; i<n; i++) {
//         //spaces
//         for(int j=0; j<i; j++) {
//             cout << " ";
//         }
//         //nums
//         for(int j=0; j<n-i; j++) {
//             cout << (i+1);
//         }
//         cout << endl;
//     }
//     return 0;
// }
// int main() {
//     int n = 4;

//     for(int i=0; i<n; i++) {
//         //spaces : n-i-1
//         for(int j=0; j<n-i-1; j++) {
//             cout << " ";
//         }
//         //nums1 : i+1
//         for(int j=1; j<=i+1; j++) {
//             cout << j;
//         }
//         //nums 2
//         for(int j=i; j>0; j--) {
//             cout << j;
//         }
//         cout << endl;
//     }
// }
//Hollow diamond pattern
// int main() {
//     int n = 4;
//     //top
//     for(int i=0; i<n; i++) {
//         //spaces
//         for(int j=0; j<n-i-1; j++) {
//             cout << " ";
//         }
//         cout << "*";

//         if(i != 0) {
//             //spaces
//             for(int j=0; j<2*i-1; j++) {
//                 cout << " ";
//             }
//             cout << "*";

//         }
//         cout << endl;
//     }
//     //bottom
//     for(int i=0; i<n-1; i++) {
//         //spaces
//         for(int j=0; j<i+1; j++) {
//             cout << " ";
//         }

//         cout << "*";
//         if(i != n-2) {
//             //spaces
//             for(int j=0; j<2*(n-i)-5; j++) {
//             cout << " ";
//         }
//             cout << "*";
//         }
//         cout << endl;

//     }

//     return 0;
// }
//function defintion
// int printHello() {
//     cout << "Hello\n";
//     return 3;
// }
//  int main() {
//     //function call or invoke
//     cout << printHello() << endl; 
//     return 0;
//  }
//sum of 2numbers
// int sum(int a, int b) {
//     int s = a + b;
//     return s;
// } 
// int main() {
//     cout << sum(10, 5) << endl;

//     return 0;
// }
// int sumN(int n) {
//     int sum = 0;

//     for(int i=1; i<=n; i++) {
//         sum += i;
//     }
//     return sum;
// }
// int main() {
//     cout << sumN(5) << endl;
//     cout << sumN(10) << endl;
//     return 0;
// }
// int factorialN(int n) {
//     int fact = 1;
//     for(int i=1; i<=n; i++) {
//         fact *= i;
//     }
//     return fact;
// }
// int main() {
//     cout << factorialN(4) << endl;
//     cout << factorialN(6) << endl;
// }
// int sumOfDigits(int num) {
//     int digSum = 0;

//     while(num > 0) {
//         int lastDig = num % 10;
//         num /= 10;
//         digSum += lastDig;
//     }
//     return digSum;
// }
// int main() {
//     cout << "Sum = " << sumOfDigits(2356);

//     return 0; 
// }
// int factorial(int n) {
//     int fact = 1;
//     for(int i=1; i<=n; i++) {
//         fact *= i;
//     }
//     return fact;
// }
// int nCr(int n, int r) {
//     int fact_n = factorial(n);
//     int fact_r = factorial(r);
//     int fact_nmr = factorial(n-r);

//     return fact_n / (fact_r * fact_nmr);
// }
// int main() {
//     int n = 8, r =2 ;
//     cout << nCr(n, r) << endl;

//     return 0;
// }
// int decToBinary(int decNum) {
//     int ans = 0, pow = 1;

//     while(decNum > 0) {
//         int rem = decNum % 2;
//         decNum /= 2;

//         ans += (rem * pow);
//         pow *= 10;
//     }
//     return ans; //binary form
// }

// int main() {
//     for(int i=1; i<=10; i++) {
//         cout << decToBinary(i) << endl;
//     }
    
//     return 0;
// }
// int binToDecimal(int binNum) {
//     int ans = 0, pow = 1;

//     while(binNum > 0) {
//         int rem = binNum % 10;
//         ans += rem * pow;

//         binNum /= 10;
//         pow *= 2;

//     }

//     return ans; //decimal form
// }

// int main() {
//     cout << binToDecimal(101) << endl;
//     return 0;
// }

// int main() {
//     int a = 4, b = 8;

//     cout << (a ^ b) << endl;
//     return 0;
// }
// int main() {
//     int nums[] = {5, 15, 22, 1, -15, -24};
//     int size = 6;

//     int smallest = INT_MAX;
    
//     for(int i=0; i<size; i++) {//min, max
//         smallest = min(nums[i], smallest);
//     }

//     cout << "smallest = " << smallest << endl;
//     return 0;
// }
// int linearSearch(int arr[], int sz, int target) {
//     for (int i=0; i<sz; i++) {
//         if(arr[i] == target) {
//             return i;
//         }
//         return -1;  //NOT FOUND
//     }

//     int main() {
//         int arr[] = {4, 2, 7, 8, 1, 2, 5};
//         int sz = 7;
//         int target = 8;

//         cout << linearSearch(arr, sz, target) << endl;
//         return 0;
//     }
// }
// int main() {
//     vector<char> vec = {'a', 'b', 'c', 'd', 'e'};

//     for(char val : vec) {//for each loop
//         cout << val << endl;
//     }
//     return 0;
// }
// int main() {
//     int n = 5;
//     int arr[5] = {1, 2, 3, 4, 5};

//     for(int st=0; st<n; st++) {
//         for(int end=st; end<n; end++) {
//             for (int i=st; i<=end; i++) {
//                 cout << arr[i];
//             }
//             cout << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }