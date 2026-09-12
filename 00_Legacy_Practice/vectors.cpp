#include <iostream>
#include <vector> //#include <bits/c++.h>
using namespace std;

/* Array like data structure (dynamic in nature) -> means size can be changed by dynamic memory allocation(runtime memory allocation in heap not stack)
STL = Standard template library(already written implementation of stacks, queues and trees also known as stl containers)*/

int main() {
    vector<int> vec;
    
    cout << "size = " << vec.size() << endl;
    
    vec.push_back(25);
    vec.push_back(35);
    vec.push_back(45);
    cout << "after push back size = " << vec.size() << endl;

    vec.pop_back(); // 45
    for(int val : vec) { // for each loop (here iterator stores value itself not the indexes of vector)
        cout << val<< endl;
    }
    cout << "after pop back size = " << vec.size() << endl;
    
    cout << vec.at(1);
    return 0;
}
