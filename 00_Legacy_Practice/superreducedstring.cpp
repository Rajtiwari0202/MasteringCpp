#include <iostream>
#include <string>
using namespace std;

string superReducedString(string s) {
    int i = 0;
    while (i < (int)s.length() - 1) {
        if (s[i] == s[i + 1]) {
            s.erase(i, 2); //reduced adjacent pairs            if (i > 0) i--;  
        } else {
            i++;
        }
    }
    return s.empty() ? "Empty String" : s;
}

int main() {
    string s;
    cin >> s;
    cout << superReducedString(s) << "\n";
    return 0;
}
