#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;        // Data stored in the node
    Node* next;      // Pointer to the next node in the linked list

    // Constructor with data and next pointer
    Node(int data1, Node* next1) {
        data = data1;
        next = next1;
    }

    // Constructor with only data, next set to nullptr
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// Convert vector to linked list and return head pointer
Node* convertArr2LL(vector<int>& arr) {
    if (arr.empty()) return nullptr;  // Handle empty input
    
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

// Print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr)
            cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);

    printList(head);  // Output: 12 -> 5 -> 8 -> 7 -> NULL

    return 0;
}
