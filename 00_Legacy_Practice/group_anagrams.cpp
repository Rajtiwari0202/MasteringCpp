#include<bits/stdc++.h>
using namespace std;

int group_anagrams1(vector<string>& strs){
    map<string,vector<string>>mpp;
    for(auto s:strs){
        string temp = s;
        sort(temp.begin(),temp.end());
        mpp[temp].push_back(s);
    }
    for(auto it:mpp){
        for(auto s:it.second){
            cout << s << " ";
        }
        cout << endl;
    }
}

int group_anagrams2(vector<string>&strs){
    //character frequency count as key
    map<map<char,int>,vector<string>>mpp;
    for(auto s:strs){
        map<char,int>freq;
        for(auto c:s){
            freq[c]++;
        }
        mpp[freq].push_back(s);
    }
    for(auto it:mpp){
        for(auto s:it.second){
            cout << s << " ";
        }
        cout << endl;
    }   
}
int main(){
    vector<string>strs = {"eat","tea","tan","ate","nat","bat"};
    group_anagrams1(strs);
    group_anagrams2(strs);
    return 0;
}