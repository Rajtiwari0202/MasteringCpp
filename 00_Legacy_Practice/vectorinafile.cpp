#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Item {
private:
    string name;
    float price;
    int qty;

public:
    Item() {}

    Item(string n, float p, int q) {
        name = n;
        price = p;
        qty = q;
    }

    // Friend functions to handle input/output
    friend ostream &operator<<(ostream &out, const Item &i);
    friend istream &operator>>(istream &in, Item &i);
};

// Overloading << operator for output
ostream &operator<<(ostream &out, const Item &i) {
    out << i.name << " " << i.price << " " << i.qty << endl;
    return out;
}

// Overloading >> operator for input
istream &operator>>(istream &in, Item &i) {
    in >> i.name >> i.price >> i.qty;
    return in;
}

int main() {
    int n;
    string name;
    float price;
    int qty;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item *> list;
    cout << "Enter all items (name, price, quantity):" << endl;

    for (int i = 0; i < n; i++) {
        cin >> name >> price >> qty;
        list.push_back(new Item(name, price, qty));
    }

    // Write to file
    ofstream fos("Items.txt");
    if (!fos) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    for (auto itr = list.begin(); itr != list.end(); itr++) {
        fos << **itr;
    }
    fos.close();

    // Read from file
    ifstream fis("Items.txt");
    if (!fis) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    cout << "\nReading from file:\n";
    Item item;
    int count = 0;
    while (fis >> item) {
        cout << "Item " << ++count << ": " << item;
    }
    fis.close();

    // Free memory
    for (auto p : list) {
        delete p;
    }

    return 0;
}
